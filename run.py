hosts = ["i1", "i3", "i4", "i5"]
n_gpus_per_host = 2
n_slaves_per_gpu = 6
n_gpu_slaves_per_gpu = 1

source_dir = "/home/sc/ssd/SC17/RELION_challenge_data"
working_dir = "/dev/shm/relion_work"
do_copy = False

gpu_cmd = "/home/yjp/relion/relion_gpu_fftw"
cpu_cmd = "/home/yjp/relion/relion_cpu_fftw"
# gpu_cmd = "xterm -e gdb -ex=r --args /home/yjp/relion/relion_gpu_fftw"
# cpu_cmd = "xterm -e gdb -ex=r --args /home/yjp/relion/relion_cpu_fftw"

# output_dir = "Class3D/job007/"
# args = "--o " + output_dir + " --i particles.star --ref run_ct24_class001.mrc --firstiter_cc --ini_high 40 --ctf --iter 40 --tau2_fudge 4 --particle_diameter 150 --K 4 --flatten_solvent --zero_mask --strict_highres_exp 10 --oversampling 1 --healpix_order 1 --sigma_ang 0.3 --offset_range 5 --offset_step 2 --sym O --norm --scale --pool 100 --dont_combine_weights_via_disc --preread_images --no_parallel_disc_io --gpu"
output_dir = "Refine3D/job007/"
args = "--o " + output_dir + " --auto_refine --split_random_halves --i particles.star --ref run_ct24_class001.mrc --firstiter_cc --ini_high 40 --ctf --particle_diameter 150 --flatten_solvent --zero_mask --oversampling 1 --healpix_order 1 --auto_local_healpix_order 5 --offset_range 5 --offset_step 2 --sym O --low_resol_join_halves 40 --norm --scale --pool 100 --dont_combine_weights_via_disc --preread_images --no_parallel_disc_io --gpu"

tmp_dir = "/home/yjp/tmp"

gpurun_sh = tmp_dir + "/gpurun.sh"
tmp_file_id = 0

n_cpu_slaves_per_gpu = n_slaves_per_gpu - n_gpu_slaves_per_gpu
n_gpus = n_gpus_per_host * len(hosts)
n_gpu_slaves = n_gpus * n_gpu_slaves_per_gpu
n_cpu_slaves = n_gpus * n_cpu_slaves_per_gpu

import os
import time

def system(cmd):
	print(cmd)
	# return 0
	ret = os.system(cmd)
	return ret

def write_script(s, fn):
	f = open(fn, "w")
	f.write(s)
	f.close()
	system("chmod +x " + fn)

def foreach_host(s):
	print(s)
	global tmp_file_id
	tmp_file_id += 1
	tmp_fn = tmp_dir + "/" + str(tmp_file_id) + ".sh"
	write_script(s, tmp_fn)
	cmd = "clush -w " + ','.join(hosts) + " " + tmp_fn;
	system(cmd)

def mps_pipe(gpu):
	return "/tmp/nvidia-mps/" + str(gpu)

def alloc_gpu_gen():
	while True:
		for gpu in range(n_gpus_per_host):
			for host in hosts:
				yield (host, gpu)

system("mkdir " + tmp_dir);
if do_copy:
	foreach_host("cp -r " + source_dir + " " + working_dir)
write_script(
	"cd " + working_dir + "\n" +
	"mkdir -p " + output_dir + "\n" +
	"export CUDA_MPS_PIPE_DIRECTORY=$1\n" + 
	"shift\n" + 
	"source /opt/intel/compilers_and_libraries_2017.4.196/linux/bin/iccvars.sh intel64\n" +
	"module load cuda/9.1\n" +
	"$@",
	gpurun_sh
)

foreach_host("sudo killall nvidia-cuda-mps-server nvidia-cuda-mps-control")
for gpu in range(n_gpus_per_host):
	foreach_host("mkdir " + mps_pipe(gpu))
	foreach_host(
		"CUDA_MPS_PIPE_DIRECTORY=" + mps_pipe(gpu) +
		" CUDA_VISIBLE_DEVICES=" + str(gpu) +
		" nvidia-cuda-mps-control -d"
	)
alloc_gpu = alloc_gpu_gen()

host, gpu = alloc_gpu.next()
cmd = "time mpirun --host " + host + " -n 1 " + \
			gpurun_sh + " " + mps_pipe(gpu) + " " + cpu_cmd + " " + args
for gpu_slave in range(n_gpu_slaves):
	host, gpu = alloc_gpu.next()
	cmd = cmd + " : --host " + host + " -n 1 " + \
			gpurun_sh + " " + mps_pipe(gpu) + " " + gpu_cmd + " " + args
for cpu_slave in range(n_cpu_slaves):
	host, gpu = alloc_gpu.next()
	cmd = cmd + " : --host " + host + " -n 1 " + \
			gpurun_sh + " " + mps_pipe(gpu) + " " + cpu_cmd + " " + args
cmd = cmd + " | tee log"
system(cmd)

foreach_host("sudo killall nvidia-cuda-mps-server nvidia-cuda-mps-control")
