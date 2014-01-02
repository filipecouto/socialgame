<?php
	require_once("PrologService/DataParser/DataParser.php");

	function getNetworkSize($Friends){
		return networkSize($Friends);
	}

	function getFriendsWithTags($Friends,$Tags){
		return friendsWithTags($Friends,$Tags);
	}

	function testDataParser(){
		return testService();
	}
?>