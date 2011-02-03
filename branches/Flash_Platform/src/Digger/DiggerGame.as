package Digger 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Timer;
	
	/**
	 * ...
	 * @author OneClick
	 */
	public class DiggerGame extends Sprite
	{
		public static var m_PlaygroundLayerBitmapData:BitmapData;
		public static var m_PlaygroundBitmap:Bitmap;
		
		private var m_Player:Player;
		private var m_Enemy:Array = new Array();
		private var m_Load:Timer;
		
		private static var m_AddRenderList:Array;
		private static var m_RemoveRenderList:Array;
		
		private var m_Level:Level;
		
		public function DiggerGame() 
		{
			DiggerResources.Load();
		}
		
		private function Load():void
		{	
			m_AddRenderList = new Array();
			m_RemoveRenderList = new Array();
			
			m_PlaygroundLayerBitmapData = new BitmapData(DiggerSetting.m_ElementWidth * DiggerSetting.m_PlaygroundWidth, DiggerSetting.m_ElementHeight * DiggerSetting.m_PlaygroundHeight);
			m_PlaygroundBitmap = new Bitmap(m_PlaygroundLayerBitmapData);
			addChild(m_PlaygroundBitmap);
			
			m_Level = new Level();
			m_Level.Load();
			
			m_Player = new Player();
			addChild(m_Player.Container);	
			
			m_Enemy[0] = new Enemy();
			m_Enemy[0].m_Position = new Point(4 * DiggerSetting.m_ElementHeight, 1 * DiggerSetting.m_ElementHeight);
			m_Enemy[0].m_PositionIndex = new Point(4, 1);
			m_Enemy[0].m_MoveToIndex = new Point(4,1);
			addChild(m_Enemy[0].m_BitmapContainer);
			
			m_Enemy[1] = new Enemy();
			m_Enemy[1].m_Position = new Point(6 * DiggerSetting.m_ElementHeight, 1 * DiggerSetting.m_ElementHeight);
			m_Enemy[1].m_PositionIndex = new Point(6, 1);
			m_Enemy[1].m_MoveToIndex = new Point(6, 1);
			addChild(m_Enemy[1].m_BitmapContainer);
			
			m_Enemy[2] = new Enemy();
			m_Enemy[2].m_Position = new Point(4 * DiggerSetting.m_ElementHeight, 3 * DiggerSetting.m_ElementHeight);
			m_Enemy[2].m_PositionIndex = new Point(4, 3);
			m_Enemy[2].m_MoveToIndex = new Point(4,3);
			addChild(m_Enemy[2].m_BitmapContainer);
			
			
			m_Enemy[3] = new Enemy();
			m_Enemy[3].m_Position = new Point(5 * DiggerSetting.m_ElementHeight, 4 * DiggerSetting.m_ElementHeight);
			m_Enemy[3].m_PositionIndex = new Point(5, 4);
			m_Enemy[3].m_MoveToIndex = new Point(5,4);
			addChild(m_Enemy[3].m_BitmapContainer);
			
			//addChild(new FPSCounter(new Point(0, 0),0x000000,true,0xFFFF00));
			
			GameStates.m_State = GameStates.GAME_IN;
		}
		
		public static function AddToRender(value:DisplayObject):void
		{
			m_AddRenderList.push(value);
		}
		
		public static function RemoveFromRender(value:DisplayObject):void
		{
			m_RemoveRenderList.push(value);
		}
		
		private function UpdateRenderList():void
		{
			var i:uint = 0;
			if (m_AddRenderList.length > 0)
			{
				for (i = 0; i < m_AddRenderList.length; ++i)
					addChildAt(m_AddRenderList.pop(),1);
			}
			
			if (m_RemoveRenderList.length > 0)
			{
				for (i = 0; i < m_RemoveRenderList.length; ++i)
					removeChild(m_RemoveRenderList.pop());
			}
		}
		
		public function Update():void
		{
			switch(GameStates.m_State)
			{
				case GameStates.GAME_PRELOAD :
					return;
				break;
				case GameStates.GAME_START :
					Load();
				break;
				case GameStates.GAME_IN :
					m_Player.State = Player.STATE_IDLE;
					if (Input.m_KeyboardCodes[37])
					{
						m_Player.State = Player.STATE_MOVE;
						m_Player.MoveRight();
					}
					if (Input.m_KeyboardCodes[39])
					{
						m_Player.State = Player.STATE_MOVE;
						m_Player.MoveLeft();
					}
					if (Input.m_KeyboardCodes[38])
					{
						m_Player.State = Player.STATE_MOVE;
						m_Player.MoveUp();
					}
					if (Input.m_KeyboardCodes[40])
					{
						m_Player.State = Player.STATE_MOVE;
						m_Player.MoveDown();
					}
					if (Input.m_KeyboardCodes[32])
					{
						m_Player.State = Player.STATE_SHOOT;
					}
					m_Player.Update();
					m_Enemy[0].Update();
					m_Enemy[1].Update();
					m_Enemy[2].Update();
					m_Enemy[3].Update();
					UpdateRenderList();
				break;
				case GameStates.GAME_PAUSE :
				
				break;
				case GameStates.GAME_END :
				
				break;
			}
		}
		
	}

}