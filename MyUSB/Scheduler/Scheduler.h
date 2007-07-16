#ifndef SCHEDULER_H
#define SCHEDULER_H

	/* Includes */
		#include <avr/io.h>
		#include <stdbool.h>

		#include "../Common/Atomic.h"
		#include "../Common/FunctionAttributes.h"

	/* Public Macros */
		#define TASK(name)                        void name (void)
		#define TASK_LIST                         extern TaskEntry_t Scheduler_TaskList[]; TaskEntry_t Scheduler_TaskList[] = 
		#define TASK_ID_LIST                      enum TaskIDs
		
		#define TASK_MAX_DELAY                    (MAX_DELAYCTR_COUNT - 1)

		#define TASK_RUN                          true
		#define TASK_STOP                         false
		
		#define Scheduler_Start()                 Scheduler_GoSchedule(TOTAL_TASKS);
		
	/* Private Macros */
		#define TOTAL_TASKS                       (sizeof(Scheduler_TaskList) / sizeof(TaskEntry_t))
		#define MAX_DELAYCTR_COUNT                0xFFFF
		
	/* Private Type Defines */
		typedef void (*TaskPtr_t)(void);

	/* Public Type Defines */
		typedef struct
		{
			uint8_t   TaskID;
			TaskPtr_t TaskName;
			bool      TaskStatus;
		} TaskEntry_t;

	/* Private Type Defines */
		typedef uint16_t SchedulerDelayCounter_t;

	/* External Variables */
		extern          TaskEntry_t               Scheduler_TaskList[];
		extern          uint8_t                   Scheduler_TotalTasks;
		extern volatile SchedulerDelayCounter_t   Scheduler_TickCounter;
	
	/* Inline Functions */
		static inline void Scheduler_GoSchedule(const uint8_t TotalTasks)
		{
			Scheduler_TotalTasks = TotalTasks;
		
			while (1)
			{
				for (uint8_t CurrTask = 0; CurrTask < TotalTasks; CurrTask++)
				{
					if (Scheduler_TaskList[CurrTask].TaskStatus == TASK_RUN)
					  Scheduler_TaskList[CurrTask].TaskName();
				}
			}
		}

		static inline void Scheduler_ResetDelay(SchedulerDelayCounter_t* TaskCounter)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				*TaskCounter = Scheduler_TickCounter;
			}
		}
		
	/* Function Prototypes */
		bool Scheduler_HasDelayElapsed(const uint16_t Delay, SchedulerDelayCounter_t* TaskCounter) ATTR_WARN_UNUSED_RESULT;
		void Scheduler_SetTaskMode(const uint8_t id, const bool run);

#endif
