use std::env;

fn main() {
  let args: Vec<String> = env::args().collect();
  let status = if args.len() < 2 {
    ""
  } else {
    &*args[1]
  };
  let arr: Vec<String> = status.split(',').map(|s| s.to_string()).collect();
  if arr.len() < 7 {
    println!("Usage: login_status $(curl http://net.tsinghua.edu.cn/rad_user_info.php)");
    return;
  }
  let delta = (arr[2].parse::<i32>().unwrap() - arr[1].parse::<i32>().unwrap()) / 60;
  if delta > 0 {
    let msg = if delta < 60 { delta.to_string() + " minutes" }
      else if delta < 60 * 24 { format!("{} hours and {} minutes", delta / 60, delta % 60) }
      else { format!("{} days, {} hours and {} minutes", delta / (60 * 24), (delta / 60) % 24, delta % 60) }
      ;
    println!("User: {}", arr[0]);
    println!("Since login: {}", msg);
  }
  let mut traffic = arr[6].parse::<f64>().unwrap();
  if traffic < 1000.0 {
    println!("Traffic: {} Bytes", traffic);
  } else {
    let names = "KMG";
    let mut level = 0;
    while traffic >= 1000.0 && level < 3 {
      traffic /= 1000.0;
      level += 1;
    }
    println!("Traffic: {:.2} {}B", traffic, names.chars().nth(level - 1).unwrap());
  }
}