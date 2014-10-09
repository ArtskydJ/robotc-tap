#include "tap.c"

task main() {

	tTest("the test suite works");
		tPlan(5); //change the number to comply and stuff
		tOk(true);
		tNotOk(false, "not ok ever!");
		tEqual(17, 83-66, "83-56=17");
		tNotEqual(10, 100, "ten ain't a hundred!");
		tPass("oh yes");

	tTest("this is the second test");
		tFail("failing # TODO make this not fail");
		tFail("skipping # SKIP make this skip");

	tTest("the test suite works");
		tPlan(3); //change the number to comply and stuff
		tEqual(17, 17, "17=17");
		tEqual(10, 10, "ten ain't a hundred!");
		tPass("such win");

	tEnd();
}
