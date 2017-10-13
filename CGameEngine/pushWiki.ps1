

param (
    [string]$wikiDir = $(throw "-wikiDir is required.")
)

Try
{
	echo $wikiDir
	$dir = Resolve-Path $wikiDir
	echo $dir
	cd $dir
	git add -A
	git commit -m "Automated Wiki Updates"
	git push
}
Catch
{
	$ErrorMessage = $_.Exception.Message
	echo $ErrorMessage
	break
}