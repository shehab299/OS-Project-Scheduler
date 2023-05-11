#pragma once


#include "DS/LinkedLish.h"
#include "../Entities/Process.h"

class ProcessList : public List<Process*>
{
public:
	Process* searchById(int id, int& pos);
};


