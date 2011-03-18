package game.core 
{
	import common.loader.BitmapLoader;
	import flash.display.DisplayObjectContainer;
	import flash.display.Stage;
	/**
	 * ...
	 * @author ...
	 */
	public class Core 
	{
		
		public static const k_CONTENT_PATH:String = "Content/";
		
		private static var m_stage:Stage = null;
		
		private static var m_displayContainer:DisplayObjectContainer = null;
		
		private static var m_bitmapLoader:BitmapLoader = null;
		
		private static var m_camera:Camera = null;
		
		private static var m_input:Input = null;
		
		public static function set stage(_value:Stage):void
		{
			m_stage = _value;
		}
		
		public static function get stage():Stage
		{
			return m_stage;
		}
		
		public static function set displayContainer(_value:DisplayObjectContainer):void
		{
			m_displayContainer = _value;
		}
		
		public static function get displayContainer():DisplayObjectContainer
		{
			return m_displayContainer;
		}
		
		public static function get bitmapLoader():BitmapLoader
		{
			if (m_bitmapLoader == null)
			{
				m_bitmapLoader = new BitmapLoader();
			}
			
			return m_bitmapLoader;
		}
		
		public static function get camera():Camera
		{
			if (m_camera == null)
			{
				m_camera = new Camera();
			}
			
			return m_camera;
		}
		
		public static function get input():Input
		{
			if (m_input == null)
			{
				m_input = new Input();
			}
			
			return m_input;
		}
		
		public static function init():void
		{
			m_camera = new Camera();
			m_input = new Input();
		}
		
	}

}