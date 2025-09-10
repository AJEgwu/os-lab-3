# Lab 3: Fork and Exec

Root directory: ./lab3.1

## What’s included
- Demos in `src/`: `fork_demo`, `exec_demo`, `pipe_demo`, `pipeline_demo`, `zombie_demo`
- Challenges in `challenges/`: ch1_single_fork, ch2_multi_child, ch3_exec_ls, worker, ch4_exec_worker, ch5_exec_examples, ch6_pipe_sum, ch7_pipeline, ch8_wait_nonblock, ch9_zombie, ch10_pool
- Build: Makefile

## How to build
make

## How to run (examples)
./bin/fork_demo
./bin/exec_demo
./bin/pipe_demo
./bin/pipeline_demo "\.c$"
./bin/zombie_demo
./bin/ch2_multi_child 5
./bin/ch7_pipeline "\.c$"
./bin/ch8_wait_nonblock
./bin/ch10_pool 3 file1 file2 file3 file4 file5


## Notes
- `zombie_demo` and `ch9_zombie` require two terminals to capture STAT=Z with `ps`.

