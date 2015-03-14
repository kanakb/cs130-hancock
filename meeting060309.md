# Rundown #

  * One last bug
  * Documentation updates
  * Presentation finalization
  * Report
  * Documentation updates

# 1 Issue #

  * Current behavior: When a task fails, its dependencies start (and will eventually fail because their input is incorrect)
  * Expected behavior: When a task fails, it marks all of its dependents as failed as well. Thus, they will never be run.
  * Recommended approach (from Sargis and Mary): When a task fails, mark it and all its dependencies as UNSUCCESSFUL. Also, add a state so that when we see a failed task, we mark all its children as UNSUCCESSFUL. Thus, we have the correct data and behavior in our program.
  * Assigned to: Mary, Michael, Sargis. If any of you has time, please make the change as soon as you can.

# Documentation Updates #

  * Updated use cases (Sargis, Mary)
  * Updated Action UML (Sargis)
  * Updated Scheduler UML (Michael)

# Report #

  * See course website for details; it's due Friday of finals week
  * Kanak will provide Known Issues

# Presentation #

  * Aiming for 12-14 minute talk, 6-8 minute demo