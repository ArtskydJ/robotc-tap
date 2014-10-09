//tap.c
//Test Anything Protocal suite
//Joseph Dykstra
//2014-10-09
//Version 1.0.0

#define DEF_ASSERT_MSG   "(unnamed assert)"
#define DEF_TEST_MSG     "(unnamed test)"

int _plan = -1;
int _on = 0;
int _pass = 0;
int _fail = 0;
int _overallFail = 0;
int _overallPass = 0;
int _overallTests = 0;
bool _loggedTapVersion = false;


void _logTapVersion() {
	if (!_loggedTapVersion) {
		writeDebugStreamLine("TAP version 13");
	}
	_loggedTapVersion = true;
}

void _logPlan(int n) {
	_logTapVersion();
	writeDebugStreamLine("1..%d", n);
}

void _log(char *message="", int number=-1) {
	if (message != "") {
		if (number != -1) {
			writeDebugStreamLine("# %s %d", message, number);
		} else {
			writeDebugStreamLine("# %s", message);
		}
	} else {
		writeDebugStreamLine("");
	}

}

void _assert(int got, int expected, char *message=DEF_ASSERT_MSG, bool shouldEqual=true) {
	_logTapVersion();
	bool skip = (stringFind(message, "# SKIP") != -1);
	bool todo = (stringFind(message, "# TODO") != -1);
	_on++;
	bool isEqual = (got == expected);
	string okStr = (isEqual == shouldEqual? "ok" : "not ok");
	writeDebugStreamLine("%s %d %s", okStr, _on, message);
	if (isEqual != shouldEqual) {
		if (!todo && !skip) {
			writeDebugStreamLine(
				"  ---\n  got: %d\n  %s:%d\n  ...",
				got,
				shouldEqual? "expected" : "did not expect",
				expected
			);
			_fail++;
		}
	} else {
		_pass += (todo? 2 : (skip? 0 : 1));
	}
}

//FUNCTIONS FOR THE USER
// tTest(msg)
// tPlan(num)
// tOk(got, msg)
// tNotOk(got, msg)
// tEqual(got, exp, msg)
// tNotEqual(got, exp, msg)
// tPass(msg)
// tFail(msg)
// tEnd(msg)

void tPlan(int set) {
	if (_plan == -1) {
		_plan = set;
		_logPlan(set);
	}
}

void tOk(bool got, char *message=DEF_ASSERT_MSG) {
	_assert(got, true, message);
}

void tNotOk(bool got, char *message=DEF_ASSERT_MSG) {
	_assert(got, true, message, false);
}

void tEqual(int got, int expected, char *message=DEF_ASSERT_MSG) {
	_assert(got, expected, message);
}

void tNotEqual(int got, int expected, char *message=DEF_ASSERT_MSG) {
	_assert(got, expected, message, false);
}

void tPass(char *message=DEF_ASSERT_MSG) {
	_assert(true, true, message);
}

void tFail(char *message=DEF_ASSERT_MSG) {
	_assert(false, true, message);
}

void _checkPlan() {
	if (_overallTests > 0) {
		if (_plan == -1) _logPlan(_on);
		else if (_on != _plan) tFail("plan does not match number of tests");
	}
	_log();
	_overallFail += _fail;
	_overallPass += _pass;
	_overallTests += _on;
}

void tTest(char *message=DEF_TEST_MSG) { //=DEF_TEST_MSG
	_logTapVersion();
	_checkPlan();
	_log(message);
	_plan = -1;
	_on = 0;
	_pass = 0;
	_fail = 0;
}

void tEnd() {
	_checkPlan();
	if (_overallTests) _log("tests", _overallTests);
	if (_overallPass) _log("pass", _overallPass);
	if (_overallFail) _log("fail", _overallFail);
	_log();
	_log(_overallFail? "not ok" : "ok");
}
