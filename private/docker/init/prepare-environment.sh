#!/bin/sh

if [ ! -z "${WWW_DATA_UID}" ]; then
    usermod -u "${WWW_DATA_UID}" www-data
fi

# Make sure files folders exists and are owned by www-data.
mkdir -p /var/www/html/sites/default/files/private
chown -R www-data /var/www/html/sites/default/files
mkdir -p /var/www/html/sites/default/private
chown -R www-data /var/www/html/sites/default/private

# Put cron file into function.
if [ -r /etc/cron.d/cron.conf ]; then
    # We do a cp to make sure the file is owned by root (the .conf
    # file is mounted into the volume and is owned by the outside user
    # -- besides that the . in the name makes it ignore by crond).
    cp /etc/cron.d/cron.conf /etc/cron.d/cron
    chown root:root /etc/cron.d/cron
fi
