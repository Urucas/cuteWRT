// this is damn easy... it cant be true!
$(document).ready(function(){

	/* global methods */
	
	/* close your app, the name is pretty obviuos */
	$('#closeBtt').click(function(){
		cuteWRT.close();
	});

	/* audio player example */
	/* creates a audio player for a streaming connection */
	var player  = cuteWRT.createAudioPlayer();
  	
	// url without error
	//player.setSource("http://69.61.11.208:8005/az");
    	
	// url with error	
    	//player.setSource("http://69.61.11.208:8000/az");

	player.onStateChangeError = function(msg) { 
		$('#error').text("Wops! London is drowing and I, I live by the river!"); 
	}
	player.onStateChangePlaying = function() { 
		$('#stopBtt').show();
		$('#playBtt').hide();		
	}
	player.onStateChangeStopped = function() {
		$('#stopBtt').hide();
		$('#playBtt').show();
	}	
	
	$('#stopBtt').click(function(){ player.stop(); });
	$('#playBtt').click(function(){ player.play(); });


	/* download manager example */
	var downloadManager = cuteWRT.createDownloadManager();

	downloadManager.onStateChangeStarted = function() {
		$('#downloadBtt').hide();
		$('#fileBtt').hide();	
		$('#progress').text('0%');
		$('#downloadMsg').text("Downloading percent:");
	}
	downloadManager.onStateChangeProgress = function(percent) {		
		$('#progress').text(percent.toString() + '%');
	}
	downloadManager.onStateChangeFinished = function() {
		$('#progress').hide();
		$('#fileBtt').hide();
		$('#downloadMsg').text("Holy wacamole!");
		$('#downloadPlayBtt').show();
	}
	$('#fileBtt').click(function(){
		if(downloadManager.fileExists('audioslave_your_savior.mp3')) {
			$('#downloadMsg').text("You already download the file!");
		}
		else {
			$('#downloadMsg').text("What are you waiting? Download the damn file!");
		}
	});
	$('#downloadBtt').click(function(){
		if(downloadManager.fileExists('audioslave_your_savior.mp3')) return;
		downloadManager.download("http://200.114.165.186/test.mp3", "audioslave_your_savior.mp3").toString();		
	});
	$('#downloadPlayBtt').click(function(){		
		var path = downloadManager.getBasepath("audioslave_your_savior.mp3");
		player.setSource(path);
	});
	$('#listBtt').click(function(){
		$('#fileList').html("");
		var list = downloadManager.listFiles();
		var xhtml = "";
		for(key in list) {
			xhtml += "<p>" + list[key] + "</p>";
		}
		$('#fileList').html(xhtml);
	});

	$('#audiotabBtt').click(function(){		
		$('.tab').hide();
		$('#audio_tab').show();
	});
	$('#downtabBtt').click(function(){		
		$('.tab').hide();
		$('#download_tab').show();
	});
	$('#dbtabBtt').click(function(){		
		$('.tab').hide();
		$('#daatabase_tab').show();
	});

	try {
		var databaseManager = cuteWRT.createDatabaseManager();
		if(!databaseManager.tableExists("radios")) {
			databaseManager.createTable("radios", [
				{ "field" : "id", "type" : "integer", "primary_key" : true , "auto_increment" : true}, 
				{ "field" : "url_stream", "type" : "varchar(300)", "default" : "http://" }, 
				{ "field" : "active", "type" : "integer", "default" : 1 }
			]);
		}
		else{
			var radios = databaseManager.select("radios", {"fields" : ["id", "url_stream"], "where" : "id = 2", "order" : "id"});
			alert(radios.length); 
		}

	}catch(e) {
		alert(e.toString());
	}
});
