

/* This file was generated by PyPe9 version 0.2 on Fri 09 Apr 21 12:09:06PM */

#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#include "StdpSongAbbott.h"
#include "exceptions.h"
#include "kernel_manager.h"
#include "dict.h"
#include "integerdatum.h"
#include "doubledatum.h"
#include "dictutils.h"
#include "numerics.h"
#include "universal_data_logger_impl.h"


/******************************************************************
 * Template specialization that needs to be in the nest namesapce *
 ******************************************************************/

nest::RecordablesMap<nineml::StdpSongAbbott> nineml::StdpSongAbbott::recordablesMap_;

namespace nest{
  template <> void RecordablesMap<nineml::StdpSongAbbott>::create() {
    insert_("tlast_post", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::tlast_post_INDEX>);
    insert_("tlast_pre", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::tlast_pre_INDEX>);
    insert_("deltaw", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::deltaw_INDEX>);
    insert_("M", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::M_INDEX>);
    insert_("P", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::P_INDEX>);
    insert_("wsyn", &nineml::StdpSongAbbott::get_y_elem_<nineml::StdpSongAbbott::State_::wsyn_INDEX>);
    insert_(CURRENT_REGIME, &nineml::StdpSongAbbott::get_current_regime_index);
  }
}

/************************************************
 * Evaluation of dynamics for a single timestep *
 ************************************************/

namespace nineml {

extern "C" void StdpSongAbbott_dump_gsl_state(gsl_odeiv2_evolve * e, double y[]) {

    std::cout << "y0:";
    for (unsigned int i = 0; i < e->dimension; ++i)
        std::cout << e->y0[i] << " ";
    std::cout << std::endl;
    std::cout << "yerr:";
    for (unsigned int i = 0; i < e->dimension; ++i)
        std::cout << e->yerr[i] << " ";
    std::cout << std::endl;
    std::cout << "dydt_in:";
    for (unsigned int i = 0; i < e->dimension; ++i)
        std::cout << e->dydt_in[i] << " ";
    std::cout << std::endl;
    std::cout << "dydt_out:";
    for (unsigned int i = 0; i < e->dimension; ++i)
        std::cout << e->dydt_out[i] << " ";
    std::cout << std::endl;
    std::cout << "last_step:" << e->last_step << std::endl;
    std::cout << "count:" << e->count << std::endl;
    std::cout << "failed_steps:" << e->failed_steps << std::endl;
    std::cout << "y:";
    for (unsigned int i = 0; i < e->dimension; ++i)
        std::cout << y[i] << " ";
    std::cout << std::endl;

}

std::string StdpSongAbbott::ExceededMaximumSimultaneousTransitions::message() {
    std::ostringstream msg;
    msg << "Exceeded maxium number of simultaneous transitions (" << num_transitions << ")";
    msg << " in " << model << " at " << t << " ms. Probable infinite loop.";
    return msg.str();
}


StdpSongAbbott::Regime_::~Regime_() {
    for (std::vector<OnCondition_*>::iterator it = on_conditions.begin(); it != on_conditions.end(); ++it)
        delete *it;
    for (std::vector<OnEvent_*>::iterator it = on_events.begin(); it != on_events.end(); ++it)
        delete *it;
}

StdpSongAbbott::Transition_* StdpSongAbbott::Regime_::transition(double end_of_step_t) {

    // Get vector of transitions (both OnConditions and OnEvents) that are triggered in the current timestep
    std::vector<Transition_*> occurred;
    for (std::vector<OnCondition_*>::iterator it = on_conditions.begin(); it != on_conditions.end(); ++it)
        if ((*it)->triggered(end_of_step_t))
            occurred.push_back(*it);

    for (std::vector<OnEvent_*>::iterator it = on_events.begin(); it != on_events.end(); ++it)
        if ((*it)->received())
            occurred.push_back(*it);

    // Get the earliest transition to be triggered
    Transition_* transition;
    if (!occurred.size())
        transition = NULL;
    else if (occurred.size() == 1)
        transition = occurred[0];
    else {
        std::vector<double> times;
        for (std::vector<Transition_*>::iterator it = occurred.begin(); it != occurred.end(); ++it)
            times.push_back((*it)->time_occurred(end_of_step_t));
        int min_index = std::min_element(times.begin(), times.end()) - times.begin();
        transition = occurred[min_index];
    }
    // Deactivate the transition trigger (if on-condition) so that it doesn't
    // 'fire' before its trigger condition has transitioned back from true to false again.
    if (transition)
        transition->deactivate();

    return transition;
}


void StdpSongAbbott::Regime_::set_triggers() {
    // Check whether trigger should be activated
    for (std::vector<OnCondition_*>::iterator it = on_conditions.begin(); it != on_conditions.end(); ++it)
        (*it)->set_trigger();
}



/**
 *  Dynamics and transitions for sole regime
 */


/* Jacobian for the sole regime if required by the solver */


StdpSongAbbott::soleRegime_::soleRegime_(StdpSongAbbott* cell)
  : Regime_(cell, "sole", SOLE_REGIME) {

    // Construct OnConditions specific to the regime.
    on_conditions.push_back(new soleOnCondition0(this));
    on_conditions.push_back(new soleOnCondition1(this));

    // Construct OnConditions specific to the regime.
    on_events.push_back(new soleOnpresynaptic_spikeEvent(this));
    on_events.push_back(new soleOnpostsynaptic_spikeEvent(this));

}

StdpSongAbbott::soleRegime_::~soleRegime_() {
}

void StdpSongAbbott::soleRegime_::init_solver() {

}

void StdpSongAbbott::soleRegime_::step_ode() {
}

// Transition methods for sole regime


bool StdpSongAbbott::soleOnpresynaptic_spikeEvent::body() {
    // Map all variables/expressions to the local namespace that are required to evaluate the state assignments that were not required for the triggers


    State_& S_ = regime->cell->S_;
    Buffers_& B_ = regime->cell->B_;
    const Parameters_& P_ = regime->cell->P_;
    Variables_& V_ = regime->cell->V_;

    // Get the next weight and remove it from the unprocessed list
    double_t weight_ = B_.presynaptic_spike_events->front();
    B_.presynaptic_spike_events->pop_front();

    // Get time stored in state
    double t = S_.t;

        
    // State Variables
    const double_t& tlast_post = S_.y_[StdpSongAbbott::State_::tlast_post_INDEX];  // (ms)
    const double_t& tlast_pre = S_.y_[StdpSongAbbott::State_::tlast_pre_INDEX];  // (ms)
    const double_t& deltaw = S_.y_[StdpSongAbbott::State_::deltaw_INDEX];  // (1)
    const double_t& M = S_.y_[StdpSongAbbott::State_::M_INDEX];  // (1)
    const double_t& P = S_.y_[StdpSongAbbott::State_::P_INDEX];  // (1)
    const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
        

    // Parameters
    const double_t& tauLTP = P_.tauLTP;  // (ms)
    const double_t& aLTP = P_.aLTP;  // (1)
    const double_t& tauLTD = P_.tauLTD;  // (ms)
    const double_t& wmax = P_.wmax;  // (1)

    // Analog receive ports

    // Constants

    // Random variables

    // Aliases



    // State assignments
    S_.y_[StdpSongAbbott::State_::P_INDEX] = P*exp((-t + tlast_pre)/tauLTP) + aLTP;  // (1)
    S_.y_[StdpSongAbbott::State_::tlast_pre_INDEX] = t;  // (ms)
    S_.y_[StdpSongAbbott::State_::deltaw_INDEX] = M*wmax*exp((-t + tlast_post)/tauLTD);  // (1)
    S_.y_[StdpSongAbbott::State_::wsyn_INDEX] = deltaw + wsyn;  // (1)

    // Output events

    return true;  // Transition contains discontinuous changes in state
}


bool StdpSongAbbott::soleOnpostsynaptic_spikeEvent::body() {
    // Map all variables/expressions to the local namespace that are required to evaluate the state assignments that were not required for the triggers


    State_& S_ = regime->cell->S_;
    Buffers_& B_ = regime->cell->B_;
    const Parameters_& P_ = regime->cell->P_;
    Variables_& V_ = regime->cell->V_;

    // Get the next weight and remove it from the unprocessed list
    double_t weight_ = B_.postsynaptic_spike_events->front();
    B_.postsynaptic_spike_events->pop_front();

    // Get time stored in state
    double t = S_.t;

        
    // State Variables
    const double_t& tlast_post = S_.y_[StdpSongAbbott::State_::tlast_post_INDEX];  // (ms)
    const double_t& tlast_pre = S_.y_[StdpSongAbbott::State_::tlast_pre_INDEX];  // (ms)
    const double_t& deltaw = S_.y_[StdpSongAbbott::State_::deltaw_INDEX];  // (1)
    const double_t& M = S_.y_[StdpSongAbbott::State_::M_INDEX];  // (1)
    const double_t& P = S_.y_[StdpSongAbbott::State_::P_INDEX];  // (1)
    const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
        

    // Parameters
    const double_t& tauLTP = P_.tauLTP;  // (ms)
    const double_t& tauLTD = P_.tauLTD;  // (ms)
    const double_t& aLTD = P_.aLTD;  // (1)
    const double_t& wmax = P_.wmax;  // (1)

    // Analog receive ports

    // Constants

    // Random variables

    // Aliases



    // State assignments
    S_.y_[StdpSongAbbott::State_::M_INDEX] = M*exp((-t + tlast_post)/tauLTD) - aLTD;  // (1)
    S_.y_[StdpSongAbbott::State_::tlast_post_INDEX] = t;  // (ms)
    S_.y_[StdpSongAbbott::State_::deltaw_INDEX] = P*wmax*exp((-t + tlast_pre)/tauLTP);  // (1)
    S_.y_[StdpSongAbbott::State_::wsyn_INDEX] = deltaw + wsyn;  // (1)

    // Output events

    return true;  // Transition contains discontinuous changes in state
}


bool StdpSongAbbott::soleOnCondition0::body() {
    // Map all variables/expressions to the local namespace that are required to evaluate the state assignments that were not required for the triggers


    State_& S_ = regime->cell->S_;
    Buffers_& B_ = regime->cell->B_;
    const Parameters_& P_ = regime->cell->P_;
    Variables_& V_ = regime->cell->V_;


    // Get time stored in state
    double t = S_.t;

        
    // State Variables
        

    // Parameters
    const double_t& wmax = P_.wmax;  // (1)

    // Analog receive ports

    // Constants

    // Random variables

    // Aliases



    // State assignments
    S_.y_[StdpSongAbbott::State_::wsyn_INDEX] = wmax;  // (1)

    // Output events

    return true;  // Transition contains discontinuous changes in state
}


bool StdpSongAbbott::soleOnCondition1::body() {
    // Map all variables/expressions to the local namespace that are required to evaluate the state assignments that were not required for the triggers


    State_& S_ = regime->cell->S_;
    Buffers_& B_ = regime->cell->B_;
    const Parameters_& P_ = regime->cell->P_;
    Variables_& V_ = regime->cell->V_;


    // Get time stored in state
    double t = S_.t;

        
    // State Variables
        

    // Parameters
    const double_t& wmin = P_.wmin;  // (1)

    // Analog receive ports

    // Constants

    // Random variables

    // Aliases



    // State assignments
    S_.y_[StdpSongAbbott::State_::wsyn_INDEX] = wmin;  // (1)

    // Output events

    return true;  // Transition contains discontinuous changes in state
}


double StdpSongAbbott::soleOnpresynaptic_spikeEvent::time_occurred(double end_of_step_t) {
    //FIXME: Should use the exact spike time specified in the spike event
    return end_of_step_t;
}


bool StdpSongAbbott::soleOnpresynaptic_spikeEvent::received() {
    return (bool)regime->cell->B_.presynaptic_spike_events->size();
}


double StdpSongAbbott::soleOnpostsynaptic_spikeEvent::time_occurred(double end_of_step_t) {
    //FIXME: Should use the exact spike time specified in the spike event
    return end_of_step_t;
}


bool StdpSongAbbott::soleOnpostsynaptic_spikeEvent::received() {
    return (bool)regime->cell->B_.postsynaptic_spike_events->size();
}

bool StdpSongAbbott::soleOnCondition0::triggered(double end_of_step_t) {

    if (active) {
        const State_& S_ = regime->cell->S_;
        const Buffers_& B_ = regime->cell->B_;
        const Parameters_& P_ = regime->cell->P_;

        // Use time at end of the ODE step to check whether the on-condition is triggered within it.
        double t = end_of_step_t;

            
        // State Variables
        const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
            

        // Parameters
        const double_t& wmax = P_.wmax;  // (1)

        // Analog receive ports

        // Constants

        // Random variables

        // Aliases



        return wsyn > wmax;
    } else
        return false;

}

void StdpSongAbbott::soleOnCondition0::set_trigger() {

    if (!active) {
        const State_& S_ = regime->cell->S_;
        const Buffers_& B_ = regime->cell->B_;
        const Parameters_& P_ = regime->cell->P_;

        // Get time stored in state
        double t = S_.t;

            
        // State Variables
        const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
            

        // Parameters
        const double_t& wmax = P_.wmax;  // (1)

        // Analog receive ports

        // Constants

        // Random variables

        // Aliases



        active = wsyn < wmax;
    }
}

double StdpSongAbbott::soleOnCondition0::time_occurred(double end_of_step_t) {
    // The trigger expression doesn't soley (in terms of state-vars) depend on 't' so just return the end of the window
    double t = end_of_step_t;
    return t;
}

bool StdpSongAbbott::soleOnCondition1::triggered(double end_of_step_t) {

    if (active) {
        const State_& S_ = regime->cell->S_;
        const Buffers_& B_ = regime->cell->B_;
        const Parameters_& P_ = regime->cell->P_;

        // Use time at end of the ODE step to check whether the on-condition is triggered within it.
        double t = end_of_step_t;

            
        // State Variables
        const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
            

        // Parameters
        const double_t& wmin = P_.wmin;  // (1)

        // Analog receive ports

        // Constants

        // Random variables

        // Aliases



        return wsyn < wmin;
    } else
        return false;

}

void StdpSongAbbott::soleOnCondition1::set_trigger() {

    if (!active) {
        const State_& S_ = regime->cell->S_;
        const Buffers_& B_ = regime->cell->B_;
        const Parameters_& P_ = regime->cell->P_;

        // Get time stored in state
        double t = S_.t;

            
        // State Variables
        const double_t& wsyn = S_.y_[StdpSongAbbott::State_::wsyn_INDEX];  // (1)
            

        // Parameters
        const double_t& wmin = P_.wmin;  // (1)

        // Analog receive ports

        // Constants

        // Random variables

        // Aliases



        active = wsyn > wmin;
    }
}

double StdpSongAbbott::soleOnCondition1::time_occurred(double end_of_step_t) {
    // The trigger expression doesn't soley (in terms of state-vars) depend on 't' so just return the end of the window
    double t = end_of_step_t;
    return t;
}



/**********************************************
 * Calculation of the residual for IDA solver *
 **********************************************/


/***********************
 * Steady-sate solvers *
 ***********************/




/****************
 * Constructors *
 ****************/

StdpSongAbbott::StdpSongAbbott()
    : Archiving_Node(),
      P_(),
      S_(P_, (Regime_*)NULL),
      B_(*this) {

    construct_regimes();
    S_.current_regime = regimes[0];

    recordablesMap_.create();

}

StdpSongAbbott::StdpSongAbbott(const StdpSongAbbott& n)
    : Archiving_Node(n),
      P_(n.P_),
      S_(n.S_),
      B_(n.B_, *this) {

    construct_regimes();

    // Update current_regime in state to match regimes in this component.
    bool found_matching_regime = false;
    for (std::vector<Regime_*>::iterator regime_it = regimes.begin(); regime_it != regimes.end(); ++regime_it)
        if ((*regime_it)->get_name() == S_.current_regime->get_name()) {
            assert(!found_matching_regime);
            S_.current_regime = *regime_it;
            found_matching_regime = true;
        }
    assert(found_matching_regime);
}

/**
 * Constructs all regimes (and their transitions) in the component class
 */
void StdpSongAbbott::construct_regimes() {

    // Construct all regimes in order of their index
    regimes.push_back(new soleRegime_(this)) ;

    // Set target regimes in all transitions
    for (std::vector<Regime_*>::iterator regime_it = regimes.begin(); regime_it != regimes.end(); ++regime_it) {
        for (std::vector<OnEvent_*>::iterator on_event_it = (*regime_it)->on_events.begin(); on_event_it != (*regime_it)->on_events.end(); ++on_event_it)
            (*on_event_it)->set_target_regime(regimes);
        for (std::vector<OnCondition_*>::iterator on_condition_it = (*regime_it)->on_conditions.begin(); on_condition_it != (*regime_it)->on_conditions.end(); ++on_condition_it)
            (*on_condition_it)->set_target_regime(regimes);
    }
}

void StdpSongAbbott::init_node_(const Node& proto) {
    const StdpSongAbbott& pr = downcast<StdpSongAbbott>(proto);
    P_ = pr.P_;
    S_ = State_(P_, regimes[0]);
}

void StdpSongAbbott::init_state_(const Node& proto) {
    const StdpSongAbbott& pr = downcast<StdpSongAbbott>(proto);
    S_ = State_(pr.P_, regimes[0]);
}

/**************
 * Destructor *
 **************/

StdpSongAbbott::~StdpSongAbbott () {
    // Destruct all regimes
    for (std::vector<Regime_*>::iterator it = regimes.begin(); it != regimes.end(); ++it)
        delete *it;
    regimes.clear();
}


/**********************************
 * Define parameters of the model *
 **********************************/

StdpSongAbbott::Parameters_::Parameters_()
:    tauLTP (0.0),
    aLTP (0.0),
    tauLTD (0.0),
    aLTD (0.0),
    wmax (0.0),
    wmin (0.0) {
// Check constraints on parameters
}

/************************************
 * Construct state from parameters.
 ************************************/

StdpSongAbbott::State_::State_(const Parameters_& p, Regime_* current_regime) :
  current_regime(current_regime) {

    const Parameters_ *params = &p;

    // FIXME: need to add initial state here
    y_[tlast_post_INDEX] = 0.0;
    y_[tlast_pre_INDEX] = 0.0;
    y_[deltaw_INDEX] = 0.0;
    y_[M_INDEX] = 0.0;
    y_[P_INDEX] = 0.0;
    y_[wsyn_INDEX] = 0.0;

    // Initialise time state just before t=0 to allow triggers at t=0 to be set
    t = -std::numeric_limits<double>::min();

}

/***********************************
 * Copy constructor for State class
 ***********************************/
StdpSongAbbott::State_::State_(const State_& s) :
  current_regime(s.current_regime), t(s.t) {

   for (int i = 0; i < 6; ++i)
       y_[i] = s.y_[i];
}

/********************************************
 * Assignment of a State from another State *
 ********************************************/

StdpSongAbbott::State_& StdpSongAbbott::State_::operator=(const State_& s) {
  assert(this != &s);
    for (size_t i = 0 ; i < 6 ; ++i)
        y_[i] = s.y_[i];

    // Copy current regime and time
    current_regime = s.current_regime;
    t = s.t;

    return *this;
}

void StdpSongAbbott::calibrate() {

    // Check that the current regime is in the regimes vector
    bool found_current_regime = false;
    for (std::vector<StdpSongAbbott::Regime_*>::iterator regime_it = regimes.begin(); regime_it != regimes.end(); ++regime_it)
        if (*regime_it == S_.current_regime)
            found_current_regime = true;
    assert(found_current_regime);
    S_.current_regime->init_solver();
    B_.logger_.init();
    V_.rng_ = nest::kernel().rng_manager.get_rng( get_thread() );
}

/***************************
 * Accessors and Modifiers *
 ***************************/

void StdpSongAbbott::Parameters_::get (DictionaryDatum &d_) const {

    // Update dictionary from internal parameters, scaling if required.
    def<double_t>(d_, "tauLTP", tauLTP);
    def<double_t>(d_, "aLTP", aLTP);
    def<double_t>(d_, "tauLTD", tauLTD);
    def<double_t>(d_, "aLTD", aLTD);
    def<double_t>(d_, "wmax", wmax);
    def<double_t>(d_, "wmin", wmin);

}

void StdpSongAbbott::Parameters_::set (const DictionaryDatum &d_) {

    // Update internal parameters from dictionary
    updateValue<double_t>(d_, "tauLTP", tauLTP);
    updateValue<double_t>(d_, "aLTP", aLTP);
    updateValue<double_t>(d_, "tauLTD", tauLTD);
    updateValue<double_t>(d_, "aLTD", aLTD);
    updateValue<double_t>(d_, "wmax", wmax);
    updateValue<double_t>(d_, "wmin", wmin);

    // Scale parameters as required
}

void StdpSongAbbott::State_::get (DictionaryDatum &d_) const {
    // Get states from internal variables
    def<double_t>(d_, "tlast_post", y_[0]);
    def<double_t>(d_, "tlast_pre", y_[1]);
    def<double_t>(d_, "deltaw", y_[2]);
    def<double_t>(d_, "M", y_[3]);
    def<double_t>(d_, "P", y_[4]);
    def<double_t>(d_, "wsyn", y_[5]);
    def<std::string>(d_, CURRENT_REGIME, current_regime->get_name());
}

void StdpSongAbbott::State_::set(const DictionaryDatum &d_, const Parameters_&, Regime_* regime) {
    // Set internal state variables from dictionary values
    updateValue<double_t>(d_, "tlast_post", y_[0]);
    updateValue<double_t>(d_, "tlast_pre", y_[1]);
    updateValue<double_t>(d_, "deltaw", y_[2]);
    updateValue<double_t>(d_, "M", y_[3]);
    updateValue<double_t>(d_, "P", y_[4]);
    updateValue<double_t>(d_, "wsyn", y_[5]);

    bool found_regime = false;
    for (std::vector<StdpSongAbbott::Regime_*>::iterator regime_it = current_regime->cell->regimes.begin(); regime_it != current_regime->cell->regimes.end(); ++regime_it) {
        if (*regime_it == regime)
            found_regime = true;
    }
    assert(found_regime);

    current_regime = regime;
}

/***********
 * Buffers *
 ***********/

StdpSongAbbott::Buffers_::Buffers_(StdpSongAbbott& n)
    : logger_(n) {
    // Initialization of the remaining members is deferred to
    // init_buffers_().
}

StdpSongAbbott::Buffers_::Buffers_(const Buffers_&, StdpSongAbbott& n)
    : logger_(n) {
    // Initialization of the remaining members is deferred to
    // init_buffers_().
}

void StdpSongAbbott::init_buffers_() {

    // Clear event buffers
    B_.presynaptic_spike_event_port.clear();
    B_.postsynaptic_spike_event_port.clear();

    // Clear analog buffers

    Archiving_Node::clear_history();

    B_.logger_.reset();

    B_.step_ = nest::Time::get_resolution().get_ms();


    // Set triggers in current regime
    S_.current_regime->set_triggers();
    S_.current_regime->init_solver();

}


void StdpSongAbbott::refresh_events(const long& lag) {
    B_.presynaptic_spike_events = &B_.presynaptic_spike_event_port.get_list(lag);
    B_.postsynaptic_spike_events = &B_.postsynaptic_spike_event_port.get_list(lag);
}

/************************************************************************
 * Function to be solved for its roots be solver to exact trigger times *
 ************************************************************************/


/***********************
 * Evaluate the update *
 ***********************/

void StdpSongAbbott::update(nest::Time const & origin, const long from, const long to) {

    assert(to >= 0 && (nest::delay) from < nest::kernel().connection_manager.get_min_delay());
    assert(from < to);

    long current_steps = origin.get_steps();

    double dt = nest::Time::get_resolution().get_ms();

    for (long lag = from; lag < to; ++lag) {

        // Update time stored in state
        S_.t = origin.get_ms();

        /***** Solve ODE over timestep *****/
        S_.current_regime->step_ode();


        /***** Transition handling *****/
        // Get multiplicity incoming events for the current lag and reset multiplicity of outgoing events
        refresh_events(lag);

        // Set times for checking on-condition triggers
        double end_of_step_t = origin.get_ms() + lag * dt;  // The time at the end of the lag step

        // Pointer to the next transition
        Transition_* transition;
        int simultaneous_transition_count = 0;

        while ((transition = S_.current_regime->transition(end_of_step_t))) {  // Check for a transition (i.e. the output of current_regime->transition is not NULL) and record it in the 'transition' variable.

            double t = transition->time_occurred(end_of_step_t);  // Get the exact time the transition occurred (if trigger is a solvable expression of 't')
            if (t == S_.t) {
                ++simultaneous_transition_count;
                if (simultaneous_transition_count > MAX_SIMULTANEOUS_TRANSITIONS)
                    throw ExceededMaximumSimultaneousTransitions("StdpSongAbbott", simultaneous_transition_count, t);
            } else {
                S_.t = t;  // Update time stored in state
                simultaneous_transition_count = 0;
            }

            // Execute body of transition, flagging a discontinuity in the ODE system
            // if either the body contains state assignments (i.e. not just output
            // events) or the regime changes
            bool discontinuous = transition->body() || (transition->get_target_regime() != S_.current_regime);
            // Update the current regime
            S_.current_regime = transition->get_target_regime();
            // Set all triggers, i.e. activate all triggers for which their trigger condition
            // evaluates to false.
            S_.current_regime->set_triggers();
            // Reinitialise the solver if the was a discontinuity in the ODE system
            if (discontinuous)
                S_.current_regime->init_solver();  // Reset the solver if the transition contains state assignments or switches to a new regime.

        }

        // Update time stored in state before setting triggers
        S_.t = end_of_step_t;

        // Set active on-condition triggers before the next state update.
        // FIXME: This implementation can't detect multiple within-step
        //        triggers. Will need to use a solver that can detect zero
        //        crossings (e.g. CVODE), supply it with an appropriate
        //        equation (i.e. unwrap logical expressions and convert inequalties
        //        to equalities = 0, e.g. a < b ==> a - b == 0, (a < b) | (c > d)
        //        ==> (a - b) * (c - d) == 0, (a < b) & (c > d) ==>
        //        abs(a - b) + abs(c - d) == 0).
        S_.current_regime->set_triggers();

        /***** Send output events for each event send port *****/
        // FIXME: Need to specify different output ports in a way that can be read by the receiving nodes
        // Output events

        /***** Get analog port values *****/

        /***** Record data *****/
        B_.logger_.record_data(current_steps + lag);

    }
}

/*****************
 * Event Handles *
 *****************/

void StdpSongAbbott::handle(nest::SpikeEvent & e) {
    assert(e.get_delay_steps() > 0);

    // Get buffer for event receive port
    nest::ListRingBuffer* event_buffer;
    if (e.get_rport() == presynaptic_spike_EVENT_PORT) {
        event_buffer = &B_.presynaptic_spike_event_port;
    } else if (e.get_rport() == postsynaptic_spike_EVENT_PORT) {
        event_buffer = &B_.postsynaptic_spike_event_port;
    } else
        assert(false);  // Unrecognised port

    const unsigned int multiplicity = e.get_multiplicity();
    const unsigned int lag = e.get_rel_delivery_steps(nest::kernel().simulation_manager.get_slice_origin());
    const double_t weight = e.get_weight();

    // Append received events to buffer
    for (unsigned int i = 0; i < multiplicity; ++i)
        event_buffer->append_value(lag, weight);

}

void StdpSongAbbott::handle(nest::CurrentEvent& e) {
    assert(e.get_delay_steps() > 0);

    //Get buffer for current receive port
    nest::RingBuffer* current_buffer;
        assert(false);  // Unrecognised port

    const double_t c = e.get_current();
    const double_t w = e.get_weight();
    const unsigned int lag = e.get_rel_delivery_steps(nest::kernel().simulation_manager.get_slice_origin());

    // Append current value for lag
    current_buffer->add_value(lag, w * c);

}

void StdpSongAbbott::handle(nest::DataLoggingRequest& e) {
    B_.logger_.handle(e);
}


}  // End 'nineml' namespace