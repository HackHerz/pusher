# Notification on SSH login

Maybe you want to receive a notification every time someone logs into your server. Just post this snippet at the end of your **/etc/profile**.


```bash
# SSH-login notification
if [ -n "${SSH_CLIENT}" ]
then
    TEXT="$(date "+%Y-%m-%d %H:%M:%S") ssh login to ${USER}@$(hostname -f)"
    TEXT+=" from $(echo "${SSH_CLIENT}" | awk '{print $1}')"
    pusher -i 297 "${TEXT}"
fi
```

Do not forget to change the id (297 in this example) to the one of your own device.
