/***************************************************************************
 *
 * Author: "Sjors H.W. Scheres"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/

#include <src/ml_optimiser_mpi.h>
#include "../timepoint.h"
#include "../pacman.h"

int main(int argc, char **argv)
{
	time_config();

	MlOptimiserMpi optimiser;
    try
    {
    	// Read in parameters from the command line
    	optimiser.read(argc, argv);

        pacman::init();

        TIME_POINT_INIT(refine);
        TIME_POINT(refine);

    	// Dirty hack to loop around movies one micrograph at a time
    	if (optimiser.do_movies_in_batches && optimiser.fn_data_movie != "" && optimiser.do_skip_maximization)
    	{
    		optimiser.processMoviesPerMicrograph(argc, argv);
            TIME_POINT(refine);
    	}
    	else
    	{
    		// normal code

			// Set things up
			optimiser.initialise();
            TIME_POINT(refine);

			// Iterate
			optimiser.iterate();
            TIME_POINT(refine);
    	}

    }
    catch (RelionError XE)
    {
//        if (optimiser.verb > 0)
//        {
//        	optimiser.usage();
//        }
    	std::cerr << XE;
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);

        return EXIT_FAILURE;

    }

    return EXIT_SUCCESS;

}

