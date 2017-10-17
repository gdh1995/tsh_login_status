#include <stdio.h>
#pragma warning(disable: 4996)

using namespace std;

int main(int argc, const char **argv)
{
  auto stat = argc >= 2 ? argv[1] : "";
  double traffic;
  long long t1, t2;
  char name[256];
  if (sscanf(stat, "%[^,],%lld,%lld,%*lld,%*lld,%*lld,%lf", name, &t1, &t2, &traffic) < 4) {
    printf("%s\n", "Usage: login_status $(curl http://net.tsinghua.edu.cn/rad_user_info.php)");
    return 0;
  }
  int delta = (int)((t2 - t1) / 60);
  if (delta > 0) {
    printf("User: %s\n", name);
    auto title = "Since Login: ";
    if (delta < 60) {
      printf("%s%d minutes\n", title, delta);
    }
    else if (delta < 60 * 24) {
      printf("%s%d hours and %d minutes\n", title, delta / 60, delta % 60);
    }
    else {
      printf("%s%d days, %d hours and %d minutes\n", title, delta / (60 * 24), (delta / 60) % 24, delta % 60);
    }
  }
  auto level = 0;
  static const char units[] = {'B', 'K', 'M', 'G'};
  while (traffic >= 1000 && level < 3) {
    traffic /= 1000;
    level += 1;
  }
  if (level) {
    printf("%s%.2lf %cB\n", "Traffic: ", traffic, units[level]);
  }
  else {
    printf("%s%d Bytes\n", "Traffic: ", (int)traffic);
  }
  return 0;
}

