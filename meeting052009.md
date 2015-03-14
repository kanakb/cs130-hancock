# Rundown #

  * Action status
  * MPane finalization
  * UI status
  * Assign work for Scheduler
  * Update documents


# Details #

  * Scheduler
    * threshold -- initially 2
      * specify from UI
      * prompt if over threshold
    * Schedule UI
    * CFG file creation
    * Pass new actions to scheduler
    * Important functions
      * add action --> specify dependencies
      * loop over actions
      * update log/MPane
      * state actions when ready
        * manage dependencies
      * report queued and active tasks
      * report times of start/end

# Assignments #
  * Kanak - finish Action dialogs, CFG file creation/edit, Scheduler UI
  * Dani - Scheduler interface
  * Michael, Mary, Sargis, Humera - Implementation of Scheduler functions
  * Prabhu - starting actions, finish MPane implementation