#include "freeossurvey.hpp"
#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

namespace freedao {

using namespace eosio;
using namespace std;

const std::string VERSION = "0.0.20";

// ACTION
void freeossurvey::version() {
  string version_message = "Version = " + VERSION; // + ", Iteration = " + to_string(current_iteration());

  check(false, version_message);
}

// verify_user - request user verification. 
[[eosio::action]]
void freeossurvey::verify( name user){
  // If returned true - surveyed or voting allowed.
  //return true;
}

[[eosio::action]]
void freeossurvey::submituser( name user, bool r0,  bool r1,  bool r2,   // Question 1
                                uint8_t r3,                    // Question 2 - slider
                                bool r4,  bool r5,  bool r6,   // Question 3  
                                uint8_t r7,                    // Question 4 - slider
                                bool r8,  bool r9,  bool r10,  // Question 5
                                bool r11, bool r12, bool r13, 
                                bool r14, bool r15, bool r16, bool r17,
                                bool r18, bool r19, bool r20) // Question 6
{ 
 // require_auth( user ); // Uncomment for production TODO!

 // check( iterationzero(),     "Iteration zero encountered. EXITING!"); 
 // 
 // check( is_active( ),        "Survey not Active!" ); 
 // verify entry data - to consider 

 // Verify user eligibility - simulation
 // - Add user to the table if new:
 
 // - Verify surveyed or not


 // - clean up/ prepare for new voting/survey 
 
 check( is_eligible( user ), "User already voted!" ); 
 
// On Frontend 
// Each rxx corresponds to exactly one choice, which can be selected under each question.
// For example if first option of the first question will be selected the corresponding
// r0 variable will be setup to true.
// On Backend
// If r0=true => results[0]++

globalres_table final_results(get_self(), get_self().value);
auto ite = final_results.begin(); 

 // Question 1: Select 2 of 3
 if(r0){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r1){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r2){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 // Question 2: result between 0-50 
 if(r3>0){final_results.modify(ite, get_self(), [&](auto &p){p.gresult = p.gresult + r3;});} ite++;
 // Question 3: Select 2 of 3
 if(r4){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r5){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r6){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++; 
 // Question 4: result between 0-50   
 if(r7>0){final_results.modify(ite, get_self(), [&](auto &p){p.gresult = p.gresult + r7;});} ite++;
 // Question 5: Select 3 of 10
 if(r8 ){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r9 ){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r10){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r11){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r12){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r13){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r14){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r15){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r16){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r17){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 // Question 6: Select 2 of 3 
 if(r18){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r19){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
 if(r20){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
//end

done( user );

// If the voting/surveing period is finished, the results are ready to pass.
       // TODO  verify the above, then pass the results.
    
//Mark user as already surveyed/voted //TODO HERE 
} //end add_results   
}