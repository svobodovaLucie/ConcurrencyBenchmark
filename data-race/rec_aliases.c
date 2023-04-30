  char *rline;
  char *cline;

void foo(char *line) {


  if (1) {
    rline = &cline;
  } else {
    cline = &rline;
  }

  *cline = 0;
}

int main() {

}