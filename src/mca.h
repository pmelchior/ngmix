/*

   Implementation of the Goodman & Weare affine invariant MCMC sampler

*/
#ifndef _MCA_HEADER_GUARD
#define _MCA_HEADER_GUARD

#include <cmath>
#include <stdexcept>
#include <sstream>
#include <vector>

namespace mca {

    class MCA {

        public:

            MCA() {
                reset(0,0,0);
            }
            MCA(size_t nwalkers, size_t nsteps_per_walker, size_t npars) {
                reset(nwalkers, nsteps_per_walker, npars);
            }

            void reset(size_t nwalkers, size_t nsteps_per_walker, size_t npars) {
                nwalkers_=nwalkers;
                nsteps_per_walker_=nsteps_per_walker;
                npars_=npars;

                nsteps_total_ = nwalkers_*nsteps_per_walker_;

                chain_.resize( nsteps_total_ * npars_ );
                lnprob_.resize( nsteps_total_);
                accept_.resize( nsteps_total_);
            }

            inline size_t get_nwalkers() const {
                return nwalkers_;
            }
            inline size_t get_nsteps_per_walker() const {
                return nsteps_per_walker_;
            }
            inline size_t get_nsteps_total() const {
                return nsteps_total_;
            }
            inline size_t get_npars() const {
                return npars_;
            }

            // Get the parameter value for the indicated walker and step. The
            // maximum step value is nsteps_per_walker, which can be gotten
            // with get_nsteps_per_walker()

            inline double get_par_bywalker(size_t walker, size_t stepnum, size_t parnum) const {

                check_args_by_walker(walker, stepnum, parnum);
                return chain_[npars_*nsteps_per_walker_*walker
                              + npars_*stepnum
                              + parnum];

            }

            // Get the parameter value for the indicated step, ignoring the
            // fact that some steps were associated with particular walkers.
            // The maximum step value is nwalkers*nsteps_per_walker-1 which can
            // be gotten from get_nstep_total()

            inline double get_par_flat(size_t stepnum, size_t parnum) const {
                check_args_flat(stepnum, parnum);
                return chain_[npars_*stepnum + parnum];
            }

        private:

            inline void check_args_by_walker(size_t walker, size_t stepnum, size_t parnum) const {
                if (stepnum > (nsteps_per_walker_-1)) {
                    std::stringstream err;
                    err << "stepnum by walker must be within [0,"
                        <<(nsteps_per_walker_-1)<<"], got"<<stepnum<<"\n";
                    throw std::runtime_error(err.str());
                }
                check_parnum(parnum);
            }
            inline void check_args_flat(size_t stepnum, size_t parnum) const {
                if (stepnum > (nsteps_total_-1)) {
                    std::stringstream err;
                    err << "flat stepnum must be within [0,"
                        <<(nsteps_total_-1)<<"], got"<<stepnum<<"\n";
                    throw std::runtime_error(err.str());
                }
                check_parnum(parnum);
            }


            inline void check_parnum(size_t parnum) const {
                if (parnum > (npars_-1)) {
                    std::stringstream err;
                    err << "parnum bust we within [0,"
                        <<(npars_-1)<<"], got"<<parnum<<"\n";
                    throw std::runtime_error(err.str());
                }
            }

            size_t nwalkers_;
            size_t nsteps_per_walker_;
            size_t nsteps_total_;
            size_t npars_;
            
            // size nwalkers*nsteps_per_walker*npars
            std::vector<double> chain_;
            // size nwalkers*nsteps_per_walker
            std::vector<double> lnprob_;
            // size nwalkers*nsteps_per_walker
            std::vector<int> accept_;

    };



}

#endif
