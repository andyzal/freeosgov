#pragma once
#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

namespace freedao {
using namespace eosio;
using namespace std;

class[[eosio::contract("freeossurvey")]] freeossurvey : public contract {

public:
  using contract::contract;

  [[eosio::action]] void version();

  [[eosio::action]] void surveyinit();

    /**
     * action submit_user
     * @details Acction run when user press SUBMIT on the frontend. The individual user's results
     * are added to this round global results stored in the table [global_results]. 
     * Before any operations the user's eligibility is tested. After the operation the user
     * is marked as non-eligible to prevent further submissions during the same iteration.
     * @param user - user's authorization from user's wallet through frontend.
     * @pre Requires user authorization.
     * @pre errormsg returns zero if no errors, 1 - user not authorized.
     * @pre Note - there is no need to verify that user vote/survey on correct session as
     * there is only one "current" session active. Anyway, user may vote/survey only once
     * during the current session.
     */
[[eosio::action]]  
void submituser( name user, bool r0,  bool r1,  bool r2,   // Question 1
                            uint8_t r3,                    // Question 2 - slider
                            bool r4,  bool r5,  bool r6,   // Question 3  
                            uint8_t r7,                    // Question 4 - slider
                            bool r8,  bool r9,  bool r10,  // Question 5
                            bool r11, bool r12, bool r13, 
                            bool r14, bool r15, bool r16); // Question 6


  // P R I V A T E //

  private:

    //---  
    //void ins_result( bool rr){
    //if (rr) {  final_results.modify(ite, get_self(), [&](auto &p) {
    //         p.g.result = gresult + 1; 
    //       });}
    //ite++; //always
    //}
    //
    //void ins_slider( uint8_t rr ){
    //Note Slider result. 
    //if ( rr>0 ) { final_results.modify(ite, get_self(), [&](auto &p) {
    //       p.g_result = gresult + rr; // Note: Count Average when survey period finished.
    //                                   // Note: Require to know the number of users voted/surveyed.  
    //     });}
    //  ite++; //always
    //}
    //---

  //  /**
  //  * action is_open
  //  * @details answer true if event is currently valid (in a given period of time)
  //  * @pre event_start and event_close should be pre-defined in external config //TODO
  //  */ 
  //  [[eosio::action]] 
  //  bool is_open(event_start, event_close) {
  //  	// is current time fit to the given period ? if yes ... //TODO 
  //    is_open = true;
  //  }
  // 
  //  /**
  //   * action is_surveyed
  //   * @details true if user already surveyed - should be not allowed for next survey
  //   * in current time period
  //   */
  //  bool is_surveyed(event_start, event_close) {
  //    // is current time fit into time pariod //TODO
  //    is_surveyed = false;
  //  }

  //This table will be abandoned after integration. TEST ONLY - Remove Later
  TABLE user_struct {
      name     user;
      bool     yesyoucan;   
      uint64_t timestamp; // not used
      uint32_t whatever;  // not used
      uint64_t primary_key() const {return user.value; }
  };
  using user_table = eosio::multi_index<"useres"_n, user_struct>;  


  // Table to count and keep survey global results for other modules
  TABLE globalres_struct {
  	  uint64_t p_key;
  	  uint32_t gresult;
  	  uint64_t primary_key() const { return p_key; }
  };
  using globalres_table = eosio::multi_index<"globalres"_n, globalres_struct>;


    TABLE status_messages { // Message numbers for the latest event
    uint64_t key;
    uint8_t  errorno;
    auto primary_key() const { return key; }
  };
  using messages_table = eosio::multi_index<"messages"_n, status_messages>;

  bool is_eligible( name user ){ //function
  user_table user_list( get_self(), get_self().value ); 
  auto idx = user_list.find(user.value); 
  if( idx == user_list.end() ) 
  {
    user_list.emplace( get_self(), [&]( auto& row ){
    row.user = user;
    row.yesyoucan = true; // new user
    });
    return true;
  }
  else 
  { 
    //Not modify - return the content
    return idx->yesyoucan; //whatever
  } 
} //end

void done( name user ){
  user_table user_list( get_self(), get_self().value ); 
  auto idx = user_list.find(user.value); 
  if( idx == user_list.end() ) 
  {
    check( false, "Broken code");
    // ...or do nothing.
  }
  else 
  { //Mark user as done
    user_list.modify(idx, get_self(), [&]( auto& row ) { row.yesyoucan = false; });
  }  
} //end

}; // end of public: contract ...  
} //namespace end





     