# Modifying headers

## Exploit
Among the quite frankly stupid comments on the `${URL}/index.php?page=e43ad1fdc54babe674da7c7b8f0127bde61de3fbe01def7d00f151c2fcca6d1c` page, we can see a comment telling us to come from `https://www.nsa.gov/` and another telling us to ues the browser `ft_bornToSec`, let's do that using curl
```shell
$  curl -H 'Referer: https://www.nsa.gov/' \
        -H 'User-Agent: ft_bornToSec' \
        '${URL}/index.php?page=e43ad1fdc54babe674da7c7b8f0127bde61de3fbe01def7d00f151c2fcca6d1c' | grep flag
```

## Fix
I guess the point here is to show us that HTTPS header can be easily modified? Don't rely on them to hide data.
