package game.ui 
{
	import common.ui.UIControl;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import game.core.Core;
	/**
	 * ...
	 * @author ...
	 */
	public class MainMenu extends UIControl 
	{
		protected var m_eventListener:Function = null;
		
		public static const k_UI_BUTTON_LEFT_DOWN:int = 1;
		public static const k_UI_BUTTON_RIGHT_DOWN:int = 2;
		public static const k_UI_BUTTON_LEFT_UP:int = 3;
		public static const k_UI_BUTTON_RIGHT_UP:int = 4;
		
		public static const k_UI_BUTTON_UP_DOWN:int = 5;
		public static const k_UI_BUTTON_DOWN_DOWN:int = 6;
		public static const k_UI_BUTTON_UP_UP:int = 7;
		public static const k_UI_BUTTON_DOWN_UP:int = 8;
		
		public static const k_UI_BUTTON_CARD_01_CLICK:int = 9;
		
		private static var m_background:Object = null;
		
		public static function get background():Object
		{
			return m_background;
		}
		
		public function MainMenu(_resName:String, _container:DisplayObjectContainer, _eventListener:Function) 
		{
			super(_resName, _container, onResLoad);
			m_eventListener = _eventListener;
			init();
		}
		
		private function init():void
		{
			
		}
		
		private function onUpdate(_event:Event):void
		{
		
		}
		
		private function onResLoad():void
		{
			m_container.addChild(m_source.card_01);
			m_container.addChild(m_source.card_02);
			m_container.addChild(m_source.card_03);
			m_container.addChild(m_source.card_04);
			
			m_container.addChild(m_source.button_left);
			m_container.addChild(m_source.button_right);
			m_container.addChild(m_source.button_up);
			m_container.addChild(m_source.button_down);
			Core.displayContainer.addChildAt(m_source.back, 0);
			m_background = m_source.back;
			
			m_source.button_left.addEventListener(MouseEvent.MOUSE_DOWN, onLeftButtonDown);
			m_source.button_right.addEventListener(MouseEvent.MOUSE_DOWN, onRightButtonDown);
			m_source.button_left.addEventListener(MouseEvent.MOUSE_UP, onLeftButtonUp);
			m_source.button_right.addEventListener(MouseEvent.MOUSE_UP, onRightButtonUp);
			
			m_source.button_up.addEventListener(MouseEvent.MOUSE_DOWN, onUpButtonDown);
			m_source.button_down.addEventListener(MouseEvent.MOUSE_DOWN, onDownButtonDown);
			m_source.button_up.addEventListener(MouseEvent.MOUSE_UP, onUpButtonUp);
			m_source.button_down.addEventListener(MouseEvent.MOUSE_UP, onDownButtonUp);
			
			m_source.card_01.addEventListener(MouseEvent.CLICK, onCard01Click);
		}
		
		private function onLeftButtonDown(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_LEFT_DOWN);
		}
		
		private function onRightButtonDown(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_RIGHT_DOWN);
		}
		
		private function onLeftButtonUp(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_LEFT_UP);
		}
		
		private function onRightButtonUp(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_RIGHT_UP);
		}
		
		
		private function onUpButtonDown(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_UP_DOWN);
		}
		
		private function onDownButtonDown(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_DOWN_DOWN);
		}
		
		private function onUpButtonUp(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_UP_UP);
		}
		
		private function onDownButtonUp(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_DOWN_UP);
		}
		
		private function onCard01Click(_event:MouseEvent):void
		{
			m_eventListener(this,k_UI_BUTTON_CARD_01_CLICK);
		}
		
	}

}