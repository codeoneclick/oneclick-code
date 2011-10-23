package core
{	
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.filters.GlowFilter;
	import flash.text.TextField;
	import flash.text.TextFormat;

	public class GameMouseIcon extends MouseIcon
	{
		[Embed(source="../../res/mouse_icons.swf", symbol="root_mouse_icons")]
		private static var Icons:Class;
		
		public static const k_ICON_CURSOR:int = 1;
		public static const k_ICON_HAND:int = 2;
				
		private var m_standardIcons:MovieClip;
		
		public function GameMouseIcon(container:DisplayObjectContainer)
		{
			super(container);
			m_standardIcons = new Icons as MovieClip;
		}
				
		public function setStandardIcon(icon:int):void
		{
			m_standardIcons.gotoAndStop(icon);
			setStaticIcon(m_standardIcons);
		}
		
		public function setElementIcon(_name:String):void
		{			
			Global.resourceController.loadPNG(_name, onLoadIcon);
		}
		
		public function get currentIcon():int
		{
			return m_standardIcons.currentFrame;
		}
	}
}