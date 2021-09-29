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

/**
 * Action surveyinit initialize new surveying period removing data of previous
 * surveying period.
 * 
*/
[[eosio::action]]
void freeossurvey::surveyinit(){
  // Warning: Table final_results is initialized by "false" and "0" respectively.
  // Warning: In table "users_list" the field "yesyoucan" setup to false for each user.
globalres_table final_results(get_self(), get_self().value);


// Note: All rows must be initialized to zero for all types of questions. 
uint64_t pkey = 0;
for(uint8_t i=0; i<20; i++) // eventually initialize or reset final_results table.
{
 auto idx = final_results.find( pkey ); 
    if( idx == final_results.end() )
    {
      final_results.emplace( get_self(), [&]( auto& row ){
        row.p_key = final_results.available_primary_key(); 
        if(i==18){ row.gresult=1; } else row.gresult = 0;
      });
    }
    else 
    { 
      final_results.modify(idx, get_self(), [&]( auto& row ) {  
        row.gresult = 0;         
      }); 
    } 
    pkey++;
} //end of for
} // end of surveyinit

[[eosio::action]]
void freeossurvey::submituser( name user, bool r0,  bool r1,  bool r2,   // Question 1
                                uint8_t r3,                    // Question 2 - slider
                                bool r4,  bool r5,  bool r6,   // Question 3  
                                uint8_t r7,                    // Question 4 - slider
                                bool r8,  bool r9,  bool r10,  // Question 5
                                bool r11, bool r12, bool r13, 
                                bool r14, bool r15, bool r16)  // Question 6
{ 
 // require_auth( user ); // Uncomment for production TODO!

 // check( iterationzero(),     "Iteration zero encountered. EXITING!"); 
 // 
 // check( is_active( ),        "Survey not Active!" ); 

 // Verify user eligibility - simulation
 // - Add user to the table if new:
 
///check( is_eligible( user ), "User already voted!" ); //Commented for test //TODO 
 
// On Frontend 
// Each rxx corresponds to exactly one choice, which can be selected under each question.
// For example if first option of the first question will be selected the corresponding
// r0 variable will be setup to true.
// On Backend
// If r0=true => final_results[0]++ (increment number of answers for this choice).

/**
 * In table "final_results": 
 *    rows 0 - 2   Question One   (three options).
 *    row  3       Question Two   (slider) - there is up to date average result.
 *    rows 4  -  6 Question Three (three options).
 *    row  7       Question Four  (slider) - there is up to date average result.
 *    rows 8  - 13 Question Five  (six options).
 *    rows 14 - 16 Question Six   (three options).
 *    row  17      Number of users submitted surveys up to date.
 *    row  18      Sum of all slider values for row 3 to count average.
 *    row  19      Sum of all slider values for row 7 to count average.  
*/  

//Verify entry data (user submitted).
uint8_t q1=0;
if(r0){q1++;};
if(r1){q1++;};
if(r2){q1++;};
check( q1==1, "First question not answered correctly");
check( ((r3>0)&&(r3<=50)), "Second question out of range 1-50");
q1=0;
if(r4){q1++;};
if(r5){q1++;};
if(r6){q1++;};
check( q1==1, "Third question not answered correctly");
check( ((r7>0)&&(r7<=50)), "Fourth question out of range 1-50");
q1=0;
if(r8){q1++;};
if(r9){q1++;};
if(r10){q1++;};
if(r11){q1++;};
if(r12){q1++;};
if(r13){q1++;};
check( q1==3, "Fifth question not answered correctly");
q1=0;
if(r14){q1++;};
if(r15){q1++;};
if(r16){q1++;};
check( q1==1, "Sixth question not answered correctly");

//Add user's results to the global
globalres_table final_results(get_self(), get_self().value);
auto ite = final_results.begin(); 

uint64_t p_key=17; //Add user to the counter at position 17 of final_results table.
auto iter = final_results.find(p_key); {final_results.modify(iter, get_self(),[&](auto &p)
  { p.gresult++; });};  
double counter = iter->gresult;           // Duplicated final_results[17].
//Total sum for sliders is going to final_results[18] and final_results[19] respectively:
iter++; final_results.modify(iter, get_self(), [&](auto &p){p.gresult = p.gresult + r3;});
double sum1 = iter->gresult;              // Duplicated final_results[18].
iter++; final_results.modify(iter, get_self(), [&](auto &p){p.gresult = p.gresult + r7;});
double sum2 = iter->gresult;              // Duplicated final_results[19].

// Question 1: Select 1 of 3
if(r0){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r1){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r2){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
// Question 2: result between 0-50   //using r3
{final_results.modify(ite, get_self(), [&](auto &p){p.gresult = sum1/counter;});} ite++;
// Question 3: Select 1 of 3
if(r4){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r5){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r6){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++; 
// Question 4: result between 0-50   //using r7
{final_results.modify(ite, get_self(),[&](auto &p){p.gresult = sum2/counter;});} ite++;
// Question 5: Select 3 of 6
if(r8 ){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r9 ){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r10){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r11){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r12){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r13){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
// Question 6: Select 1 of 3 
if(r14){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r15){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
if(r16){final_results.modify(ite, get_self(),[&](auto &p){ p.gresult++; });} ite++;
//end

///done( user );

// If the voting/surveing period is finished, the results are ready to pass.
       // TODO  verify the above, then pass the results.
    
//Mark user as already surveyed/voted //TODO HERE 
} //end add_results   
}