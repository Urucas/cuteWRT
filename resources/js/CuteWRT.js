function CuteWRT(){ 	
	this.audioPlayer = null;	
	this.downloadManager = null;
	this.databaseManager = null;
	this.createAudioPlayer = function(){ if(this.audioPlayer == null) { _cuteWRT.createAudioPlayer(); this.audioPlayer = new CuteWRTAudioPlayer(); } return this.audioPlayer; }
	this.createDownloadManager = function() { if(this.downloadManager == null) { _cuteWRT.createDownloadManager(); this.downloadManager = new CuteWRTDownloadManager(); } 	return this.downloadManager; }	
	this.createDatabaseManager = function() { if(this.databaseManager == null) { _cuteWRT.createDatabaseManager(); this.databaseManager = new CuteWRTDatabaseManager(); } 	return this.databaseManager; }
	this.setPreferenceForKey = function(value, key) { if(value == undefined || key == undefined) return false; _cuteWRT.setPreferenceForKey(value.toString(), key.toString()); }
	this.getPreferenceForKey = function(key) { if(key == undefined) return false; return _cuteWRT.getKey(key.toString()).toString(); }
	this.debug = function(msg) { msg = msg == undefined ? "Param msg is not valid" : msg; _cuteWRT.debug(msg.toString()); }
	this.close = function() { _cuteWRT.close(); }
	this.setDisplayPortrait = function() { _cuteWRT.setDisplayPortrait(); }
	this.setDisplayLandscape = function() { _cuteWRT.setDisplayLandscape(); }
	this.setDisplay = function(display){ if(display == undefined) return false; if(display.toString()=="portrait") _cuteWRT.setDisplayPortrait; else if(display.toString()=="landscape") _cuteWRT.setDisplayLandscape(); }
}
function CuteWRTDownloadManager(){
	this.download = function(src, nam) { if(src == undefined || nam == undefined) return; _cuteWRTDownloadManager.download(src.toString(), nam.toString()); }
	this.listFiles = function() { return JSON.parse(_cuteWRTDownloadManager.listDownloadedFiles().toString()); }
	this.fileExists = function(src) { if(src == undefined) return false; return _cuteWRTDownloadManager.fileExists(src.toString());}
	this.getBasepath = function(src) { if(src == undefined) return false; return _cuteWRTDownloadManager.getBasepath(src.toString()).toString(); }
	this.onStateChangeStarted = function() {}
	this.onStateChangeProgress = function() {}
	this.onStateChangeFinished = function(){};
	this.onStateChangeError = function(){};
}
function CuteWRTAudioPlayer(){	
	this.setSource = function(src) { if(src == undefined) return; _cuteWRTAudioPlayer.setSource(src.toString()); }
	this.getSource = function() { return _cuteWRTAudioPlayer.getSource().toString(); }
	this.play = function() { _cuteWRTAudioPlayer.play(); }
	this.stop = function() { _cuteWRTAudioPlayer.stop(); }
	this.pause = function() { _cuteWRTAudioPlayer.pause(); }	
	this.getState = function() { return parseInt(_cuteWRTAudioPlayer.getState()); }
	this.volDown = function() { _cuteWRTAudioPlayer.volDown(); }
	this.volUp = function() { _cuteWRTAudioPlayer.volUp(); }
	this.mute = function() { _cuteWRTAudioPlayer.mute(); }
	this.onStateChangeError = function(msg) {}
	this.onStateChangePlaying = function() {}
	this.onStateChangeStopped = function() {}
	this.onStateChangeLoading = function() {}
	this.onStateChangeBuffering =  function(){}
	this.onStateChangePaused = function(){}
}
function CuteWRTDatabaseManager(){
	this.showTables = function() { return JSON.parse(_cuteWRTDatabaseManager.showTables().toString()); }
	this.tableExists = function(table) { if(table == undefined) return false; return _cuteWRTDatabaseManager.tableExists(table.toString()); }
	this.createTable = function(table, fields) { if(table == undefined || fields == undefined) return false; return _cuteWRTDatabaseManager.createTable(table.toString(), JSON.stringify(fields).toString()); }
	this.select = function(table, params){ if(table == undefined) return false; params = params == undefined ? [] : params; return JSON.parse(_cuteWRTDatabaseManager.select(table.toString(), JSON.stringify(params).toString()).toString());}	
	this.onDatabaseConnectionError = function(msg) {}
	this.getLastError = function() { return _cuteWRTDatabaseManager.getlastError().toString(); }
}
var cuteWRT = new CuteWRT();
