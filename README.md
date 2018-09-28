robotc-tap
==========

[Test Anything Protocol](http://testanything.org/tap-version-13-specification.html) for [RobotC](http://robotc.net). Basically a bunch of unit test helper functions, that outputs to the debug stream.

# How To

1. Click [Download Zip](https://github.com/ArtskydJ/robotc-tap/archive/master.zip).
2. Copy the `tap.c` file to the directory that you want to test.
3. Create a unit test file, maybe `test.c`, or `run_Tests.c`.
4. In the file, write `#include "tap.c"`.
5. Use the [Functions](#functions) provided.
6. Compile and run your unit test file.


# Example

```c
#include "tap.c"

task main() {

	tTest("the test suite works");
		tOk(true);
		tNotOk(false, "not ok ever!");
		tEqual(17, 83-66, "83-56=17");
		tNotEqual(10, 100, "ten ain't a hundred!");
		tPass("oh yes");

	tTest("this is the second test");
		tFail("failing # TODO make this not fail");
		tFail("skipping # SKIP make this skip");

	tTest("the test suite works");
		tEqual(17, 17, "17=17");
		tEqual(10, 10, "ten ain't a hundred!");
		tPass("such win");
	tEnd(); //Only run this at the end
}
```

# Functions

For a quick and dirty namespace solution, internal global variables and functions start with "_", and user functions start with "t" (for test).

## `tTest(string msg)`

This starts a new set of tests, and resets some internal counters. This also ends the previous set of tests, if there was one.

Code:
```c
tTest("my function is awesome");
```
Output:
```
# my function is awesome
```

## `tOk(bool test, string message)`

This checks if `test` is `true`.

Code:
```c
tOk(bLcdBacklight, "the backlight is on");
```
Output:
```
ok 1 the backlight is on
```

## `tNotOk(bool test, string message)`

This checks if `test` is `false`.

Code:
```c
tNotOk(bLcdBacklight, "the backlight is off");
```
Output:
```
ok 2 the backlight is off
```

## `tEqual(int test, int expected, string message)`

This checks if `test` equals `expected`.

Code:
```c
tEqual(motor[MY_MOTOR], 127, "MY_MOTOR is running full speed.");
```
Output:
```
ok 3 MY_MOTOR is running full speed.
```

## `tNotEqual(int test, int unexpected, string message)`

This checks if `test` does not equal `unexpected`.

Code:
```c
tNotEqual(motor[MY_MOTOR2], 0, "MY_MOTOR is not still");
```
Output:
```
ok 4 MY_MOTOR2 is not still
```

## `tPass(string message)`

This is a test that always passes.

Code:
```c
tPass("yay this works")
```
Output:
```
ok 5 yay this works
```

## `tFail(string message)`

This is a test that always fails.

Code:
```c
tFail("that was predictable")
```
Output:
```
not ok 6 that was predictable
  ---
  got: 0
  expected: 1
  ...
```

## `tEnd(string message)`

This ends the *last* set of tests. Use `tTest()` to end any set that isn't last.

# License

[MIT](https://choosealicense.com/licenses/mit/)

