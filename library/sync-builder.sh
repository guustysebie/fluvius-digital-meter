rsync -urltv --delete -e ssh /home/guust/projects/fluvius-digital-meter/library/ whizx@192.168.1.201:/home/whizx/bing
ssh whizx@192.168.1.201 'cd /home/whizx/bing; cmake . ; make ; echo "build done" ; '
