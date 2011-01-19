package 
{
	
	/**
	 * @author PsyTech
	 */
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.net.URLLoader;
	
	 
	public class ContentLoader 
	{
		
		public  var imagesManager     :Array;
		private var imagesLoadersList :Array;
		private var imagesLoadIndex   :int;
		public  var imagesPath        :String; 
		private var imagesLoaderTimer :Timer;
		
		
		public var sources_manager :Array;
		
		private var sources_path   :String;
		
		private var loaders_list   :Array;
		
		private  var xmlLoadersList:Array;
		
		private var sources_index  :int;
		
		private var sources_timer  :Timer;
		
		public var mainXML         :XML;
		
		private var xmlIndex       :int;
		
		private var main           :gameMatch3;
		
		public function set Path(value:String):void
		{
			this.sources_path = value;
		}
		
		public function ContentLoader(main:gameMatch3) 
		{
			this.imagesManager = new Array();
			this.imagesLoadersList = new Array();
			this.imagesLoadIndex = -1;
			this.imagesPath = "";
			this.imagesLoaderTimer = new Timer(1000);
			this.imagesLoaderTimer.addEventListener(TimerEvent.TIMER, this.onImagesLoadFinish);
			this.imagesLoaderTimer.start();
			
			
			this.sources_manager = new Array();
			this.loaders_list = new Array();
			this.xmlLoadersList = new Array();
			this.sources_index = -1;
			this.xmlIndex = 1;
			this.main = main;
			
			this.sources_timer = new Timer(100);
			this.sources_timer.addEventListener(TimerEvent.TIMER, this.OnLoadFinish);
			this.sources_timer.start();
		}
		
		public function LoadImage(name:String):void
		{
			if (this.imagesLoadIndex < 0)
				this.imagesLoadIndex = 0;
			this.imagesLoadIndex++;
			
			this.imagesLoadersList[name] = new Loader();
			this.imagesLoadersList[name].contentLoaderInfo.addEventListener(Event.COMPLETE, onLoadImage);
			this.imagesLoadersList[name].load(new URLRequest(this.imagesPath + name + ".png"));
		}
		
		private function onLoadImage(event:Event):void
		{
			var mainURL:String = event.target.url;
			var imageName:String = mainURL.substring(this.imagesPath.length + mainURL.search(this.imagesPath), mainURL.length - 4);
			trace(imageName);
			this.imagesManager[imageName] = new BitmapData(256, 256, true, 0x00FFFFFF);
			this.imagesManager[imageName].draw(this.imagesLoadersList[imageName]);
			this.imagesLoadIndex--;
		}
		
		public function Load(name:String):void
		{
			if (this.sources_index < 0)
				this.sources_index = 0; 
			this.sources_index++;
			loaders_list[name] = new Loader();
			loaders_list[name].contentLoaderInfo.addEventListener(Event.INIT, OnLoad);
			loaders_list[name].load(new URLRequest(this.sources_path + name + ".swf"));	
		}
		
		public function LoadXML(name:String):void 
		{
			xmlLoadersList[name] = new URLLoader();
			xmlLoadersList[name].addEventListener(Event.COMPLETE, onXMLLoad);
			xmlLoadersList[name].load(new URLRequest(name));
		}
		
		public function onXMLLoad(event:Event):void
		{
			var xml:XML = new XML(event.target.data);
			this.mainXML = xml;
			this.xmlIndex--;	
		}
		
		private function OnLoad(event:Event):void
		{
			var main_url:String = event.target.url;
			var name:String = main_url.substring(this.sources_path.length + main_url.search(this.sources_path), main_url.length - 4);
			sources_manager[name] = loaders_list[name].content;
			loaders_list[name].removeEventListener(Event.INIT, OnLoad);
			this.sources_index--;
		}
		
		public function UnLoad(name:String):void
		{
			loaders_list[name].unload();
		}
		
		public function dispose():void
		{
			sources_timer.stop();
			sources_timer = null;
		}
		
		private function onImagesLoadFinish(event:TimerEvent):void
		{
			if (this.imagesLoadIndex == 0) {
				this.main.initPlaneImages();
				this.imagesLoaderTimer.reset();
			}
		}
		
		private function OnLoadFinish(event:TimerEvent):void
		{
			if (this.sources_index == 0){
				this.main.initImages();
				this.sources_timer.reset();
			}	
		}
	}
	
}