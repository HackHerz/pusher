# Notification for fail2ban

Copy [pusher.conf](https://github.com/HackHerz/pusher/blob/master/examples/pusher.conf) to **/etc/fail2ban/action.d/** and insert this snippet in your *jail.local*.

```
[ssh]

enabled  = true
port     = ssh
filter   = sshd
logpath  = /var/log/auth.log
maxretry = 6
action = pusher[name=ssh, dest=ONQ]
```


Example is for SSH and change ONQ to your own Device-ID.
