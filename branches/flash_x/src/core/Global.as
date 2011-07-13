package core 
{
	import common.resource.ResourceController;
	import flash.display.DisplayObjectContainer;
	import flash.display.Stage;
	import game.SceneController;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Global 
	{
		
		private static var m_stage:Stage = null;
		
		private static var m_displayContainer:DisplayObjectContainer = null;
		
		private static var m_resourceController:ResourceController = null;
		
		private static var m_sceneController:SceneController = null;
		
		private static var m_input:Input = null;
		
		private static var m_camera:Camera = null;
		
		public function Global() 
		{
			
		}
		
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
		
		public static function get resourceController():ResourceController
		{
			if (m_resourceController == null)
			{
				m_resourceController = new ResourceController();
			}
			
			return m_resourceController;
		}
		
		public static function set sceneController(_value:SceneController):void
		{
			m_sceneController = _value;
		}
		
		public static function get sceneController():SceneController
		{
			return m_sceneController;
		}
		
		public static function set input(_value:Input):void
		{
			m_input = _value;
		}
		
		public static function get input():Input
		{
			return m_input;
		}
		
		public static function set camera(_value:Camera):void
		{
			m_camera = _value;
		}
		
		public static function get camera():Camera
		{
			return m_camera;
		}
		
	}

}