package ui 
{
	import core.GameMouseIcon;
	import core.Global;	
	import flash.display.SimpleButton;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class UICameraControls 
	{
		[Embed(source="../../res/camera_controls.swf", symbol="root_camera_controls")]
		private static var CameraControls:Class;
		
		public static const k_BUTTON_NAME_UP:String      = "button_up";
		public static const k_BUTTON_NAME_DOWN:String	= "button_down";
		public static const k_BUTTON_NAME_LEFT:String	= "button_left";
		public static const k_BUTTON_NAME_RIGHT:String	= "button_right";
		public static const k_BUTTON_NAME_CENTER:String	= "button_center";
		
		public static const k_BUTTON_UP:int 	= 1;    
		public static const k_BUTTON_DOWN:int 	= 2;
		public static const k_BUTTON_LEFT:int 	= 3;	
		public static const k_BUTTON_RIGHT:int 	= 4;
				
		public var m_state:int = 0;
		private var m_cameraControls:Sprite;
		
		public function UICameraControls() 
		{
			m_cameraControls = new CameraControls as Sprite;
			m_cameraControls.x = m_cameraControls.width / 2;
			Global.uiContainer.addChild(m_cameraControls);
			Global.stage.addEventListener(Event.RESIZE, onResize);			
			Global.stage.dispatchEvent(new Event(Event.RESIZE));
			
			var button:SimpleButton;
			button = m_cameraControls.getChildByName(k_BUTTON_NAME_UP) as SimpleButton;
			button.addEventListener(MouseEvent.MOUSE_DOWN, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_UP, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			button.addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			
			button = m_cameraControls.getChildByName(k_BUTTON_NAME_DOWN) as SimpleButton;
			button.addEventListener(MouseEvent.MOUSE_DOWN, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_UP, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			button.addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			
			button = m_cameraControls.getChildByName(k_BUTTON_NAME_LEFT) as SimpleButton;
			button.addEventListener(MouseEvent.MOUSE_DOWN, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_UP, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			button.addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			
			button = m_cameraControls.getChildByName(k_BUTTON_NAME_RIGHT) as SimpleButton;
			button.addEventListener(MouseEvent.MOUSE_DOWN, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_UP, onClickButon);
			button.addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			button.addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			
			button = m_cameraControls.getChildByName(k_BUTTON_NAME_CENTER) as SimpleButton;
			button.addEventListener(MouseEvent.CLICK, onClickButon);			
			button.addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			button.addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			
			m_cameraControls.addEventListener(Event.ENTER_FRAME, onUpdate);
			
			Global.stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			Global.stage.addEventListener(KeyboardEvent.KEY_UP, onKeyDown);
		}
		
		private function onMouseOver(event:MouseEvent):void
		{
			Global.mouseIcon.setVisibleLoadedIcon(false);
			Global.mouseIcon.setStandardIcon(GameMouseIcon.k_ICON_HAND);			
		}
		
		private function onMouseOut(event:MouseEvent):void
		{
			Global.mouseIcon.setVisibleLoadedIcon(true);
			Global.mouseIcon.setStandardIcon(GameMouseIcon.k_ICON_CURSOR);
			m_state = 0;
		}
		
		private function onUpdate(event:Event):void
		{
			if (m_state == 0) return;
			
			switch(m_state)
			{
				case k_BUTTON_UP:
				{		
					Global.camera.position = Global.camera.position.add(new Point(0, 5));
					break;
				}
				case k_BUTTON_DOWN:
				{	
					Global.camera.position = Global.camera.position.add(new Point(0, -5));
					break;
				}
				case k_BUTTON_LEFT:
				{
					Global.camera.position = Global.camera.position.add(new Point(5, 0));
					break;
				}
				case k_BUTTON_RIGHT:
				{
					Global.camera.position = Global.camera.position.add(new Point(-5, 0));
					break;
				}
			}
		}
		
		private function onKeyDown (event:KeyboardEvent):void 
		{
			var button:SimpleButton;
			
			switch(event.keyCode)
			{
				case 38:
				{
					button = m_cameraControls.getChildByName(k_BUTTON_NAME_UP) as SimpleButton;					
					break;
				}
				case 40:
				{
					button = m_cameraControls.getChildByName(k_BUTTON_NAME_DOWN) as SimpleButton;
					break;
				}
				case 37:
				{
					button = m_cameraControls.getChildByName(k_BUTTON_NAME_LEFT) as SimpleButton;
					break;
				}
				case 39:
				{
					button = m_cameraControls.getChildByName(k_BUTTON_NAME_RIGHT) as SimpleButton;
					break;
				}
				default:
				{
					return;
				}
			}
			
			if (event.type == KeyboardEvent.KEY_DOWN)
			{
				button.dispatchEvent(new MouseEvent(MouseEvent.MOUSE_DOWN));				
			}
			else if (event.type == KeyboardEvent.KEY_UP)
			{
				button.dispatchEvent(new MouseEvent(MouseEvent.MOUSE_UP));
			}
		}
		
		private function onClickButon(event:MouseEvent):void
		{
			var button:SimpleButton = event.target as SimpleButton;
			switch(button.name)
			{
				case k_BUTTON_NAME_UP:
				{
					if (event.type == MouseEvent.MOUSE_DOWN)
					{
						m_state = k_BUTTON_UP;					
					}
					else if (event.type == MouseEvent.MOUSE_UP)
					{
						m_state = 0;
					}
					break;
				}
				case k_BUTTON_NAME_DOWN:
				{
					if (event.type == MouseEvent.MOUSE_DOWN)
					{
						m_state = k_BUTTON_DOWN;
					}
					else if (event.type == MouseEvent.MOUSE_UP)
					{
						m_state = 0;
					}
					break;
				}
				case k_BUTTON_NAME_LEFT:
				{
					if (event.type == MouseEvent.MOUSE_DOWN)
					{
						m_state = k_BUTTON_LEFT;
					}
					else if (event.type == MouseEvent.MOUSE_UP)
					{
						m_state = 0;
					}
					break;
				}
				case k_BUTTON_NAME_RIGHT:
				{
					if (event.type == MouseEvent.MOUSE_DOWN)
					{
						m_state = k_BUTTON_RIGHT;
					}
					else if (event.type == MouseEvent.MOUSE_UP)
					{
						m_state = 0;
					}
					break;
				}
				case k_BUTTON_NAME_CENTER:
				{
					Global.camera.position = new Point(0, 0);
					break;
				}
			}
		}
		
		private function onResize(event:Event):void
		{
			m_cameraControls.y = Global.stage.stageHeight - m_cameraControls.height / 2;			
		}
		
		public function get cameraControlsMC():Sprite
		{
			return m_cameraControls;
		}
	}
}