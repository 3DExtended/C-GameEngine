

param (
    [string]$wikiDir = $(throw "-wikiDir is required.")
)

Try
{
	cd $wikiDir
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