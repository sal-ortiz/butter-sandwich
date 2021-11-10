// timer crappy



#ifndef _TIMER_H_
  #define _TIMER_H_

  #include <time.h>

  #define TIMER_START_CHECKPOINT_ID   "TIMER_START"


  typedef struct {
    char* id;
    unsigned long int timestamp;
  } TimerCheckpointObj;



  #define get_elapsed_runtime()   ( (float)clock() / CLOCKS_PER_SEC )
  // --------------------------------------------------------------------------


  #define get_checkpoint_id( checkpoint )   checkpoint.id
  // --------------------------------------------------------------------------


  #define get_checkpoint_timestamp( checkpoint )    ( (float)checkpoint.timestamp / CLOCKS_PER_SEC )
  // --------------------------------------------------------------------------


  inline TimerCheckpointObj checkpoint( char* id, unsigned long int timestamp ){
    TimerCheckpointObj new_checkpoint_obj;
    new_checkpoint_obj.id = id;   new_checkpoint_obj.timestamp = timestamp;

    return new_checkpoint_obj;
  } // ------------------------------------------------------------------------


  #define set_checkpoint_id( checkpoint, new_id )   (*checkpoint).id = new_id
  // --------------------------------------------------------------------------


  #define set_checkpoint_timestamp( checkpoint, new_timestamp )   (*checkpoint).timestamp = new_timestamp
  // --------------------------------------------------------------------------


  #define elapsed_time( checkpoint )    ( (float)(clock() - checkpoint.timestamp) / CLOCKS_PER_SEC )
  // --------------------------------------------------------------------------

  #define reset_timer( checkpoint )   set_checkpoint_timestamp( checkpoint, clock() )
  // --------------------------------------------------------------------------


  inline float wait( float interval ){
    unsigned long int loop_start_timestamp = clock();
    while ( (float)(clock() - loop_start_timestamp) < (float)(interval * CLOCKS_PER_SEC) ); // do nothing, just wait.

    return (float)(clock() - loop_start_timestamp) / CLOCKS_PER_SEC;
  } // ------------------------------------------------------------------------



#endif  // ifndef _TIMER_H_
