#ifndef EVENT_STRUCTURE_H
#define EVENT_STRUCTURE_H
	
typedef enum {			/*put all your possible event enum here*/
	Event1, Event2
} EventTypeEnum;

typedef struct {
	EventTypeEnum Type;
	/*if you want to hang more information with event, hang it here*/
	/*int a,c;*/
} EventClass;

#endif
