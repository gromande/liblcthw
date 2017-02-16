#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <lcthw/dbg.h>
#include <assert.h>
#include <string.h>

char *test_bfromcstr() {
  bstring b = bfromcstr("Hello");
  debug("Length: %d; BString: %s", b->slen, b->data);
  return NULL;
}

char *test_blk2bstr() {
  void *buf = "Hello";
  bstring b = blk2bstr(buf, 5);
  debug("Length: %d; BString: %s", blength(b), bdata(b));
  return NULL;
}

char *test_bstrcpy() {

}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_bfromcstr);
  mu_run_test(test_blk2bstr);

  return NULL;
}

RUN_TESTS(all_tests);
