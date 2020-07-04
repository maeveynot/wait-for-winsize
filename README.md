# wait-for-winsize

Work around a race condition in xfce4-terminal where it forks the
command and *then* does `TIOCSWINSZ` on the pty, causing programs like
`rlwrap` that need a usable value from `TIOCGWINSZ` during
initialization to fail.

Usage:

    wait-for-winsize [DELAY...]

The *n*th argument defines how long, in milliseconds, to delay after
`TIOCGWINSZ` attempt *n* (defaulting to 1ms if not specified). For
example, on my machine, the race usually takes about 10ms, so I run
`wait-for-winsize 10`; the first retry delays for 10ms and all
subsequent retries delay for 1ms.

Exits successfully if the terminal was ready, or with failure if any
retries were required.
