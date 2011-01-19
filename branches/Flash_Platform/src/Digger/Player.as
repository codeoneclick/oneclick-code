package Digger 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.TimerEvent;
	import flash.filters.BitmapFilter;
	import flash.filters.BitmapFilterQuality;
    import flash.filters.DropShadowFilter;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Dictionary;
	import flash.utils.Timer;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Player
	{
		public static var STATE_IDLE:String = "STATE_IDLE";
		public static var STATE_MOVE:String = "STATE_MOVE";
		public static var STATE_SHOOT:String = "STATE_SHOOT";
		
		public static var DIRECTION_UP:String = "UP";
		public static var DIRECTION_DOWN:String = "DOWN";
		public static var DIRECTION_LEFT:String = "LEFT";
		public static var DIRECTION_RIGHT:String = "RIGHT";
		
		private var m_Position:Point = new Point(0, 0);
		public function set Position(value:Point):void
		{
			m_Position = new Point(value.x, value.y);
		}
		
		public function get Position():Point
		{
			return new Point(m_Position.x, m_Position.y);
		}
		
		private var m_Index:Point = new Point(0, 0);
		public function set Index(value:Point):void
		{
			m_Index = new Point(value.x, value.y);
		}
		
		public function get Index():Point
		{
			return new Point(m_Index.x, m_Index.y);
		}
		
		private var m_Direction:String = DIRECTION_LEFT;
		public function get Direction():String
		{
			return m_Direction;
		}
		
		public function set Direction(value:String):void
		{
			m_Direction = value;
			
			switch(m_Direction)
			{
				case DIRECTION_UP:
					m_Container.rotation = -90;
				break;
				case DIRECTION_DOWN:
					m_Container.rotation = 90;
				break;
				case DIRECTION_LEFT:
					m_Container.rotation = 0;
				break;
				case DIRECTION_RIGHT:
					m_Container.rotation = 180;
				break;
			}
		}
		
		private var m_NextIndex:Point = new Point(0, 0);
		private var m_NextPosition:Point = new Point(0, 0);
		
		private var m_Speed:Number = 4;
		private var m_IsMove:Boolean = false;
		
		private var m_State:String = STATE_IDLE;
		public function set State(value:String):void
		{
			m_State = value;
		}
		
		private var m_BitmapData:BitmapData;
		private var m_Bitmap:Bitmap;
		private var m_Container:Sprite;
		public function get  Container():Sprite
		{
			return m_Container;
		}
		
		private var m_AnimController:AnimController = null;
		
		public static var m_Explosion:Explosion = null;
		
		public function Player() 
		{
			m_BitmapData = new BitmapData(DiggerSetting.m_ElementWidth , DiggerSetting.m_ElementHeight );
			m_Bitmap = new Bitmap(m_BitmapData);	
			m_Container = new Sprite();
			m_Bitmap.x = -m_Bitmap.width / 2;
			m_Bitmap.y = -m_Bitmap.height / 2;
			m_Container.scaleX = new Number(0.6);
			m_Container.scaleY = new Number(0.6);
			m_Container.filters = [getBitmapFilter()];
			m_Container.addChild(m_Bitmap);
			
			m_AnimController = new AnimController(m_BitmapData);
			m_AnimController.AddAnim("p_idle_", 20);
			m_AnimController.AddAnim("p_shoot_", 20);
			m_AnimController.AddAnim("player_run01_frame", 12);
			m_AnimController.AddAnim("p_hole_", 12);
			m_AnimController.StartAnim("p_idle_", true);
		}
		
		 private function getBitmapFilter():BitmapFilter {
            var color:Number = 0x000000;
            var angle:Number = 45;
            var alpha:Number = 1.0;
            var blurX:Number = 2;
            var blurY:Number = 2;
            var distance:Number = 10;
            var strength:Number = 0.8;
            var inner:Boolean = false;
            var knockout:Boolean = false;
            var quality:Number = BitmapFilterQuality.HIGH;
            return new DropShadowFilter(distance,
                                        angle,
                                        color,
                                        alpha,
                                        blurX,
                                        blurY,
                                        strength,
                                        quality,
                                        inner,
                                        knockout);
        }
		
		public static function Add():void
		{
			//m_CurrentExplosion = new Explosion(new Point(m_Position.x, m_Position.y));
		}

		
		public function MoveUp():void
		{
			if (m_IsMove) return;
			Direction = DIRECTION_UP;
			if (m_Index.y == 0) return;
			if ((Level.m_Playground[m_Index.x][m_Index.y - 1] as Element).GetType() != "element_empty_01")
			{
				m_AnimController.StartAnim("p_hole_", true);
				m_Explosion = new Explosion(new Point(m_Position.x, m_Position.y - DiggerSetting.m_ElementHeight / 2));
			}
			else
			{
				m_AnimController.StartAnim("player_run01_frame", true);
			}
			m_NextIndex.y--;
			OnMoveStart(DIRECTION_UP, DIRECTION_DOWN);
		}
		
		public function MoveDown():void
		{
			if (m_IsMove) return;
			Direction = DIRECTION_DOWN;
			if (m_Index.y == (DiggerSetting.m_PlaygroundHeight - 1)) return;
			if ((Level.m_Playground[m_Index.x][m_Index.y + 1] as Element).GetType() != "element_empty_01") 
			{
				m_AnimController.StartAnim("p_hole_", true);
				m_Explosion = new Explosion(new Point(m_Position.x, m_Position.y + DiggerSetting.m_ElementHeight / 2));
			}
			else
			{
				m_AnimController.StartAnim("player_run01_frame", true);
			}
			m_NextIndex.y++;
			OnMoveStart(DIRECTION_DOWN, DIRECTION_UP);
		}
		
		public function MoveLeft():void
		{
			if (m_IsMove) return;
			
			Direction = DIRECTION_LEFT;
			if (m_Index.x == (DiggerSetting.m_PlaygroundWidth - 1)) return;
			if ((Level.m_Playground[m_Index.x + 1][m_Index.y] as Element).GetType() != "element_empty_01") 
			{
				m_AnimController.StartAnim("p_hole_", true);
				m_Explosion = new Explosion(new Point(m_Position.x + DiggerSetting.m_ElementWidth / 2, m_Position.y));
			}
			else
			{
				m_AnimController.StartAnim("player_run01_frame", true);
			}
				
			m_NextIndex.x++;
			OnMoveStart(DIRECTION_LEFT, DIRECTION_RIGHT);
		}
		
		public function MoveRight():void
		{
			if (m_IsMove) return;
			
			Direction = DIRECTION_RIGHT;
			if (m_Index.x == 0) return;
			if ((Level.m_Playground[m_Index.x - 1][m_Index.y] as Element).GetType() != "element_empty_01") 
			{
				m_AnimController.StartAnim("p_hole_", true);
				m_Explosion = new Explosion(new Point(m_Position.x - DiggerSetting.m_ElementWidth / 2, m_Position.y));
			}
			else
			{
				m_AnimController.StartAnim("player_run01_frame", true);
			}
			m_NextIndex.x--;
			OnMoveStart(DIRECTION_RIGHT, DIRECTION_LEFT);
		}
		
		private function OnMoveStart(edge_01:String,edge_02:String):void
		{
			(Level.m_Playground[m_Index.x][m_Index.y] as Element).RemoveEdge(edge_01);
			(Level.m_Playground[m_Index.x][m_Index.y] as Element).SetType("element_empty_01");
			(Level.m_Playground[m_Index.x][m_Index.y] as Element).Update();
			(Level.m_Playground[m_NextIndex.x][m_NextIndex.y] as Element).RemoveEdge(edge_02);
			(Level.m_Playground[m_NextIndex.x][m_NextIndex.y] as Element).SetType("element_empty_01");
			(Level.m_Playground[m_NextIndex.x][m_NextIndex.y] as Element).Update();
			
			m_NextPosition = new Point(0, 0);
			m_IsMove = true;
		}
		
		public function Update():void
		{
			OnMove();
			if(m_State == STATE_IDLE && m_IsMove)
				m_State = STATE_MOVE;
			
			switch(m_State)
			{
				case STATE_IDLE :
				{
					m_AnimController.StartAnim("p_idle_", true);
				}
				break;
				case STATE_MOVE :
				{
					
				}
				break;
				case STATE_SHOOT :
				{
					m_AnimController.StartAnim("p_shoot_", false);
				}
				break;
				default :
					
			}
			
			m_Container.x = m_Position.x + m_Bitmap.width / 2;
			m_Container.y = m_Position.y + m_Bitmap.height / 2;
		}
		
		private function OnMove():void
		{
			if (!m_IsMove) return;
			switch(m_Direction)
			{
				case "UP" :
					if (m_NextPosition.y > -DiggerSetting.m_ElementHeight)
					{
						if (m_Position.y < Setting.m_Height / 2 && DiggerGame.m_PlaygroundBitmap.y < 0)
						{
							DiggerGame.m_PlaygroundBitmap.y += m_Speed;
							m_Explosion.m_DeltaPosition.y += m_Speed;
						}
						else
							m_Position.y -= m_Speed;
						m_NextPosition.y -= m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "DOWN" :
					if (m_NextPosition.y < DiggerSetting.m_ElementHeight)
					{
						if (m_Position.y > Setting.m_Height / 2 && DiggerGame.m_PlaygroundBitmap.y > -Setting.m_Height)
						{
							DiggerGame.m_PlaygroundBitmap.y -= m_Speed;
							m_Explosion.m_DeltaPosition.y -= m_Speed;
						}
						else
							m_Position.y += m_Speed;
						m_NextPosition.y += m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "LEFT" :
					if (m_NextPosition.x < DiggerSetting.m_ElementWidth)
					{
						
						if (m_Position.x > Setting.m_Width / 2  && DiggerGame.m_PlaygroundBitmap.x > -Setting.m_Width)
						{
							DiggerGame.m_PlaygroundBitmap.x -= m_Speed;
							m_Explosion.m_DeltaPosition.x -= m_Speed;
						}
						else
							m_Position.x += m_Speed;
						m_NextPosition.x += m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "RIGHT" :
					if (m_NextPosition.x > -DiggerSetting.m_ElementWidth)
					{
						if (m_Position.x < Setting.m_Width / 2 && DiggerGame.m_PlaygroundBitmap.x < 0)
						{
							DiggerGame.m_PlaygroundBitmap.x += m_Speed;
							m_Explosion.m_DeltaPosition.x += m_Speed;
						}
						else
							m_Position.x -= m_Speed; 
						m_NextPosition.x -= m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
			}
		}
		
		private function MoveEnd():void
		{
			m_IsMove = false;
			m_Index = new Point(m_NextIndex.x, m_NextIndex.y);
			(Level.m_Playground[m_NextIndex.x][m_NextIndex.y] as Element).Update();
		}

	}

}