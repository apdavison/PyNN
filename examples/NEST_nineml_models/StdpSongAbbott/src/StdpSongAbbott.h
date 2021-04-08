/* This file was generated by PyPe9 version 0.2 on Fri 02 Apr 21 07:04:09PM */

#ifndef STDPSONGABBOTT_H
#define STDPSONGABBOTT_H

#include "nest_types.h"
#include "event.h"
#include "archiving_node.h"
#include "ring_buffer.h"
#include "connection.h"
#include "universal_data_logger.h"
#include "recordables_map.h"
#include "dictutils.h"
#include "exceptions.h"

#define CURRENT_REGIME "__regime__"

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_sf_exp.h>
#include <gsl/gsl_odeiv2.h>

#define ITEM(v,i)  (v[i])
namespace nineml {
    


    class StdpSongAbbott;

    /**
     * Create a typedef for the function that represents the system of ODEs
     */ 
    typedef int (*dynamics_function_type)(double t, const double y_[], double f_[], void* pnode_);

    /**
     * Declaration of dynamics and residual signatures
     */
    extern "C" int StdpSongAbbott_sole_dynamics(double t, const double y_[], double f_[], void* pnode_);
    extern "C" int StdpSongAbbott_sole_jacobian(double t, const double y[], double *dfdy, double dfdt[], void* node);
    class StdpSongAbbott : public nest::Archiving_Node {

      public:
        class ExceededMaximumSimultaneousTransitions : public nest::KernelException {
        
          public:
            ExceededMaximumSimultaneousTransitions(const std::string& model, int num_transitions, double t)
              : KernelException("ExceededMaximumSimultaneousTransitions"), model(model), num_transitions(num_transitions), t(t) {}
            ~ExceededMaximumSimultaneousTransitions() throw () {}
            std::string message();
          protected:
             const std::string& model;
             int num_transitions;
             double t;
        };


        static const int MAX_SIMULTANEOUS_TRANSITIONS = 1000;

        class Regime_;
        class Transition_;
        class OnEvent_;
        class OnCondition_;
        class soleOnpresynaptic_spikeEvent;
        class soleOnpostsynaptic_spikeEvent;
        class soleOnCondition0;
        class soleOnCondition1;
      

        ~StdpSongAbbott();
        StdpSongAbbott(const StdpSongAbbott &);
        StdpSongAbbott();

        /**
         * Import sets of overloaded virtual functions.
         * This is necessary to ensure proper overload and overriding resolution.
         * @see http://www.gotw.ca/gotw/005.htm.
         */
        using nest::Node::handle;
        using nest::Node::handles_test_event;

        nest::port send_test_event(nest::Node&, nest::port, nest::synindex, bool);

        void handle(nest::SpikeEvent &);
        void handle(nest::CurrentEvent &);
        void handle(nest::DataLoggingRequest &);

        nest::port handles_test_event(nest::SpikeEvent &, nest::port);
        nest::port handles_test_event(nest::CurrentEvent &, nest::port);
        nest::port handles_test_event(nest::DataLoggingRequest &, nest::port);

        void get_status(DictionaryDatum &) const;
        void set_status(const DictionaryDatum &);

        void init_node_(const nest::Node& proto);
        void init_state_(const nest::Node& proto);
        void init_buffers_();
        void calibrate();
        unsigned int current_regime_index() { return S_.current_regime->get_index(); }
        
        void refresh_events(const long& lag);
        
        /* Inline random distribution methods */
        double random_uniform_(double low, double high);
        double random_normal_(double mu, double sigma);
        double random_exponential_(double lambda); 

        void update(nest::Time const &, const long, const long);
        
        Regime_* get_regime(unsigned int index) { return regimes[index]; }

    // Set dynamics methods (the ones that actually model the dynamics) as friends
        friend int StdpSongAbbott_sole_dynamics(double t, const double y_[], double f_[], void* pnode_);
          
        /* Regime ids */
        enum Regimes {
            SOLE_REGIME = 0,
            NUM_REGIMES_
        };


        /* Event port ids
         * @note Start with 1 so we can forbid port 0 to avoid accidental
         *     creation of connections with no receptor type set.
         */
        static const nest::port MIN_EVENT_PORT_ = 1;
        enum EventPorts {
            presynaptic_spike_EVENT_PORT = MIN_EVENT_PORT_,
            postsynaptic_spike_EVENT_PORT,
            SUP_EVENT_PORT_
        };

        // On event ids
        enum OnEvents {
            sole_presynaptic_spike_ON_EVENT,
            sole_postsynaptic_spike_ON_EVENT,
            SUP_ON_EVENT_
        };

        //Analog port ids
        static const nest::port MIN_ANALOG_PORT_ = 1;
        enum AnalogPorts {
            SUP_ANALOG_PORT_
        };

        // Synaptic event function definitions
        inline void presynaptic_spike_event_in_sole(long lag);
        inline void postsynaptic_spike_event_in_sole(long lag);

        // The next two classes need to be friends to access the State_ class/member
        friend class nest::RecordablesMap<StdpSongAbbott>;
        friend class nest::UniversalDataLogger<StdpSongAbbott>;

        struct Parameters_ {
            double tauLTP;
            double aLTP;
            double tauLTD;
            double aLTD;
            double wmax;
            double wmin;
            Parameters_();
            void get(DictionaryDatum&) const;
            void set(const DictionaryDatum&);
        }; // end struct Parameters_

        struct State_ {

            enum StateVecElems {
                tlast_post_INDEX = 0,
                tlast_pre_INDEX,
                deltaw_INDEX,
                M_INDEX,
                P_INDEX,
                wsyn_INDEX,
                STATE_VEC_SIZE_
            };

            // State variables vector
            double y_[STATE_VEC_SIZE_];

            // Pointer to the current regime
            Regime_* current_regime;

            // The current simulation time
            double t;  

            State_(const Parameters_& p, Regime_*);
            State_(const State_& s);
            State_& operator=(const State_& s);
            void get(DictionaryDatum&) const;
            void set(const DictionaryDatum&, const Parameters_&, Regime_*);
            std::string to_str(double t);
        }; // end struct State_

        struct Variables_ {
            librandom::RngPtr rng_;           // random number generator of thread
        };

        struct Buffers_ {
            Buffers_(StdpSongAbbott&);
            Buffers_(const Buffers_&, StdpSongAbbott&);
            nest::UniversalDataLogger<StdpSongAbbott> logger_;

            // Timesteps
            double_t step_;       //!< step size in ms

            // Event receive port buffers
            nest::ListRingBuffer presynaptic_spike_event_port;
            std::list<double_t>* presynaptic_spike_events;  // Points to the events in the current timestep.
            nest::ListRingBuffer postsynaptic_spike_event_port;
            std::list<double_t>* postsynaptic_spike_events;  // Points to the events in the current timestep.

            // Event send port count

            // Analog receive port buffers

            // Variables to hold the last value of the analog receive port buffers

        }; // end struct Buffers_
        
        class Regime_ {
         
          public:
            Regime_(StdpSongAbbott* cell, const std::string& name, unsigned int index) 
              : cell(cell), name(name), index(index) {}
            virtual ~Regime_();
            Transition_* transition(double end_of_step_t);
            void set_triggers();
            virtual void init_solver() = 0;
            virtual void step_ode() = 0;
            const std::string& get_name() { return name; }
            unsigned int get_index() { return index; }
            
           
          protected:
            StdpSongAbbott* cell;
            std::string name;  // For debugging
            unsigned int index;  // Used for identifying the regime
            std::vector<OnCondition_*> on_conditions;
            std::vector<OnEvent_*> on_events;
           
          friend class StdpSongAbbott;
          friend class Transition_;
          friend class OnEvent_;
          friend class OnCondition_;
          friend class soleOnpresynaptic_spikeEvent;
          friend class soleOnpostsynaptic_spikeEvent;
          friend class soleOnCondition0;
          friend class soleOnCondition1;
        
        };
        
        /*
         * Create a specific class for each regime in order to override the 
         * default constructor and initialise its transitions
         */
        class soleRegime_ : public Regime_ {
            
          public:
          
            // Regime-specifc indices for states that are updated by its ODE
            // system, so the regime-specifi state vector can be trunctated to
            // exclude states that aren't updated.
            enum ODEStateElem {
                ODE_STATE_VEC_SIZE_
            };
          
            soleRegime_(StdpSongAbbott* cell);
            virtual ~soleRegime_();
            virtual void init_solver();
            virtual void step_ode();
            
          protected:

            // Array containg the values for the states for the set of ODEs
            // FIXME: This should be a generic vector macro to support CVODE, etc...
            double ode_y_[ODE_STATE_VEC_SIZE_];           
            
    

          friend int StdpSongAbbott_sole_jacobian(double t, const double y[], double *dfdy, double dfdt[], void* node);
        };
        
        
        /**
         * Set up an abstract base class to define a common interface for all
         * transitions (both OnEvent and OnCondition).
         */
        class Transition_ {

          public:
            Transition_(Regime_* regime, unsigned int target_regime_index)
              : regime(regime), target_regime(NULL), target_regime_index(target_regime_index) {}
            virtual ~Transition_() {}
            Regime_* get_target_regime();            
            virtual double time_occurred(double end_of_step_t) = 0;
            virtual bool body() = 0;
            virtual void deactivate() = 0;  // Only needed for on-conditions (although might be added for on-events in the future)
            
            /* Inline random distribution methods */
            double random_uniform_(double low, double high);
            double random_normal_(double mu, double sigma);
            double random_exponential_(double lambda);
            
          protected:
            void set_target_regime(const std::vector<Regime_*>& regimes);

          protected:
            Regime_* regime;
            Regime_* target_regime;
            unsigned int target_regime_index;  // Used in the construction as a placeholder for the target regime

          friend class StdpSongAbbott;
        };
        
        
        /**
         * The base OnEvent class from which all OnEvent classes are derived
         */
        class OnEvent_ : public Transition_ {
        
          public:
            OnEvent_(Regime_* regime, unsigned int target_regime_index) : Transition_(regime, target_regime_index) {}
            virtual ~OnEvent_() {}
            virtual bool received() = 0;
            virtual void deactivate() {}  // Not required for on-events
        
        };

        /**
         * The base OnCondition class from which all OnCondition classes are derived
         */
        class OnCondition_ : public Transition_ {
          public:
            OnCondition_(Regime_* regime, unsigned int target_regime_index) : Transition_(regime, target_regime_index), active(false) {}
            virtual ~OnCondition_() {}
            virtual bool triggered(double end_of_step_t) = 0;
            virtual void set_trigger() = 0;
            void deactivate() { active = false; }
            
          protected:
            bool active;
        };
        
        /*
         * Create a specific class for each OnEvent and OnCondition that will
         * specify its trigger condition, state assignments and output events
         */
        class soleOnpresynaptic_spikeEvent : public OnEvent_ {

          public:
            soleOnpresynaptic_spikeEvent(Regime_* regime) : OnEvent_(regime, SOLE_REGIME) {}
            virtual ~soleOnpresynaptic_spikeEvent() {}
            virtual bool received();                        
            virtual double time_occurred(double end_of_step_t);
            virtual bool body();
     
        };

        class soleOnpostsynaptic_spikeEvent : public OnEvent_ {

          public:
            soleOnpostsynaptic_spikeEvent(Regime_* regime) : OnEvent_(regime, SOLE_REGIME) {}
            virtual ~soleOnpostsynaptic_spikeEvent() {}
            virtual bool received();                        
            virtual double time_occurred(double end_of_step_t);
            virtual bool body();
     
        };

        class soleOnCondition0 : public OnCondition_ {

          public:
            soleOnCondition0(Regime_* regime) : OnCondition_(regime, SOLE_REGIME) {}
            virtual ~soleOnCondition0() {}
            virtual bool triggered(double end_of_step_t);
            virtual void set_trigger();
            virtual double time_occurred(double end_of_step_t);
            virtual bool body();
        };

        class soleOnCondition1 : public OnCondition_ {

          public:
            soleOnCondition1(Regime_* regime) : OnCondition_(regime, SOLE_REGIME) {}
            virtual ~soleOnCondition1() {}
            virtual bool triggered(double end_of_step_t);
            virtual void set_trigger();
            virtual double time_occurred(double end_of_step_t);
            virtual bool body();
        };


        template <State_::StateVecElems elem>
        
        // data logger functions
        double_t get_y_elem_() const { return S_.y_[elem]; }
        double_t get_current_regime_index() const { return (double_t)S_.current_regime->get_index(); }

        Parameters_ P_;
        State_      S_;
        Variables_  V_;
        Buffers_    B_;

        //! Mapping of recordables names to access functions    
        static nest::RecordablesMap<StdpSongAbbott> recordablesMap_;
        
      protected:
        void construct_regimes();
        std::vector<Regime_*> regimes;        
    
    }; // end class StdpSongAbbott

    inline void StdpSongAbbott::Transition_::set_target_regime(const std::vector<StdpSongAbbott::Regime_*>& regimes) {
        this->target_regime = regimes[this->target_regime_index];   
    }

    inline StdpSongAbbott::Regime_* StdpSongAbbott::Transition_::get_target_regime() {
        return this->target_regime;   
    }

    inline nest::port StdpSongAbbott::send_test_event(nest::Node& target, nest::port receptor_type, nest::synindex, bool) {
        nest::SpikeEvent e;
        e.set_sender(*this);
        return target.handles_test_event(e, receptor_type);
    }

    inline nest::port StdpSongAbbott::handles_test_event(nest::SpikeEvent&, nest::port receptor_type) {
        if (receptor_type < 0 || receptor_type >= SUP_EVENT_PORT_)
            throw nest::UnknownReceptorType(receptor_type, this->get_name());
        else if (receptor_type < MIN_EVENT_PORT_)
            throw nest::IncompatibleReceptorType(receptor_type, this->get_name(), "SpikeEvent");
        return receptor_type;
    }

    inline nest::port StdpSongAbbott::handles_test_event(nest::CurrentEvent&, nest::port receptor_type) {
        if (receptor_type < 0 || receptor_type >= SUP_ANALOG_PORT_)
            throw nest::UnknownReceptorType(receptor_type, this->get_name());
        else if (receptor_type < MIN_ANALOG_PORT_)
            throw nest::IncompatibleReceptorType(receptor_type, this->get_name(), "CurrentEvent");
        return receptor_type;
    }

    inline nest::port StdpSongAbbott::handles_test_event(nest::DataLoggingRequest& dlr, nest::port receptor_type) {
        if (receptor_type != 0)
            throw nest::UnknownReceptorType(receptor_type, this->get_name());
        return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
    }

    inline void StdpSongAbbott::get_status(DictionaryDatum &d) const {
        P_.get(d);
        S_.get(d);
        nest::Archiving_Node::get_status(d);
        (*d)[nest::names::recordables] = recordablesMap_.get_list();
        def<double_t>(d, nest::names::t_spike, get_spiketime_ms());
        DictionaryDatum receptor_dict_ = new Dictionary();
        // Synaptic event dictionary
        (*receptor_dict_)[Name("presynaptic_spike")]  = presynaptic_spike_EVENT_PORT;
        (*receptor_dict_)[Name("postsynaptic_spike")]  = postsynaptic_spike_EVENT_PORT;
        (*d)[nest::names::receptor_types] = receptor_dict_;
    }

    inline void StdpSongAbbott::set_status(const DictionaryDatum &d) {
            
        // Get the regime
        long regime_index;
        updateValue<long>(d, CURRENT_REGIME, regime_index);
        if ((regime_index < 0) || (regime_index >= NUM_REGIMES_))
            regime_index = 0;  // Sanitise non-sensical value to within range (initial states are set with arbitrary values during construction)
        Regime_* regime = regimes[regime_index];
 
        Parameters_ ptmp = P_;  // temporary copy in case of errors
        ptmp.set(d);             // throws if BadProperty
        State_    stmp = S_;  // temporary copy in case of errors
        stmp.set(d, ptmp, regime);         // throws if BadProperty

        // We now know that (ptmp, stmp) are consistent. We do not
        // write them back to (P_, S_) before we are also sure that
        // the properties to be set in the parent class are internally
        // consistent.
        nest::Archiving_Node::set_status(d);
        // if we get here, temporaries contain consistent set of properties
        P_ = ptmp;
        S_ = stmp;    
        calibrate();
    }
    
    /* Inline random distributions (for deprecated format random.*), copied
       from the corresponding NEST random deviate implementations in librandom
       but stripped from RandomDeviate boiler plate */
    
    inline double StdpSongAbbott::random_uniform_(double low, double high) {
        return low + (high - low) * V_.rng_->drand();
    }

    inline double StdpSongAbbott::random_normal_(double mu, double sigma) {
        // Box-Muller algorithm, see Knuth TAOCP, vol 2, 3rd ed, p 122
        // we waste one number
        double V1;
        double V2;
        double S;

        do {
            V1 = 2 * V_.rng_->drand() - 1;
            V2 = 2 * V_.rng_->drand() - 1;
            S = V1 * V1 + V2 * V2;
        } while ( S >= 1 );

        if ( S != 0 )
            S = V1 * std::sqrt( -2 * std::log( S ) / S );
        return mu + sigma * S;
    }
    
    inline double StdpSongAbbott::random_exponential_(double lambda) {
        return -std::log(V_.rng_->drandpos()) / lambda;
    }
    
    
    inline double StdpSongAbbott::Transition_::random_uniform_(double low, double high) {
        return low + (high - low) * this->regime->cell->V_.rng_->drand();
    }

    inline double StdpSongAbbott::Transition_::random_normal_(double mu, double sigma) {
        // Box-Muller algorithm, see Knuth TAOCP, vol 2, 3rd ed, p 122
        // we waste one number
        double V1;
        double V2;
        double S;

        do {
            V1 = 2 * this->regime->cell->V_.rng_->drand() - 1;
            V2 = 2 * this->regime->cell->V_.rng_->drand() - 1;
            S = V1 * V1 + V2 * V2;
        } while ( S >= 1 );

        if ( S != 0 )
            S = V1 * std::sqrt( -2 * std::log( S ) / S );
        return mu + sigma * S;
    }
    
    inline double StdpSongAbbott::Transition_::random_exponential_(double lambda) {
        return -std::log(this->regime->cell->V_.rng_->drandpos()) / lambda;
    }

    inline std::string StdpSongAbbott::State_::to_str(double t) {
        std::stringstream ss;  
        ss << "t=" << t;
        ss << ", tlast_post=" << y_[tlast_post_INDEX];
        ss << ", tlast_pre=" << y_[tlast_pre_INDEX];
        ss << ", deltaw=" << y_[deltaw_INDEX];
        ss << ", M=" << y_[M_INDEX];
        ss << ", P=" << y_[P_INDEX];
        ss << ", wsyn=" << y_[wsyn_INDEX];
        return ss.str();
    }

} // end namespace nineml

#endif // STDPSONGABBOTT_H