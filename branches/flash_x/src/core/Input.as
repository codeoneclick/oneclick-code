package core 
{
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.ui.Mouse;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Input 
	{
		private static const k_KEY_Z:int = 90;
		
		private var m_isMouseDown:Boolean = false;
		private var m_oldMousePos:Point = new Point();
		private var m_mouseDragOffset:Point = new Point();
		private var m_cursor:Cursor = null;
		
		public function Input() 
		{
			init();
		}
		
		private function init():void
		{
			Global.inGameContainer.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Global.inGameContainer.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Global.inGameContainer.addEventListener(Event.ENTER_FRAME, onUpdate);
			
			Global.backContainer.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			Global.backContainer.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			Global.backContainer.addEventListener(Event.ENTER_FRAME, onUpdate);
			
			Global.stage.addEventListener(KeyboardEvent.KEY_UP, onKeyUp);
			
			//Mouse.hide();
			m_cursor = new Cursor(Global.inGameContainer);
			m_cursor.Load("cursor");
			m_cursor.mouseEnabled = false;
		}
		
		private function onMouseDown(_event:MouseEvent):void
		{
			m_isMouseDown = true;
		}
		
		private function onMouseUp(_event:MouseEvent):void
		{
			m_isMouseDown = false;
		}
		
		private function onUpdate(_event:Event):void
		{	
			if (m_isMouseDown)
			{
				m_mouseDragOffset.x = m_oldMousePos.x - Global.stage.mouseX;
				m_mouseDragOffset.y = m_oldMousePos.y - Global.stage.mouseY;
				
				if (m_mouseDragOffset.x != 0)
					Global.camera.position.x += m_mouseDragOffset.x;
				
				if (m_mouseDragOffset.y != 0)
					Global.camera.position.y += m_mouseDragOffset.y;
			}

			m_oldMousePos.x = Global.stage.mouseX;
			m_oldMousePos.y = Global.stage.mouseY;
		}
		
		private function onKeyUp(_event:KeyboardEvent):void
		{
			if ( _event.ctrlKey && _event.keyCode == k_KEY_Z )
			{
				Global.editorController.undo();
			}
		}
		
		public function get mousePosition():Point
		{
			return m_oldMousePos;
		}
		
	}

}