#include "test.h"
#include "gvalue.h"
#include "_sdk.h"

test* test::get()
{
	static test inst;
	return &inst;
}

void test::main()
{

}