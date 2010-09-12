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
		public static var m_BackgroundLayerBitmapData:BitmapData;
		public static var m_PlaygroundLayerBitmapData:BitmapData;
		
		public static var m_BackgroundBitmap:Bitmap;
		public static var m_PlaygroundBitmap:Bitmap;
		
		public static var m_Playground:Array;
		private var m_Player:Player;
		private var m_Load:Timer;
		
		private static var m_AddRenderList:Array;
		private static var m_RemoveRenderList:Array;
		
		public function DiggerGame() 
		{
			DiggerResources.Load();
		}
		
		private function Load():void
		{
			//m_BackgroundLayerBitmapData = new BitmapData(DiggerSetting.m_ElementWidth * DiggerSetting.m_PlaygroundWidth, DiggerSetting.m_ElementHeight * DiggerSetting.m_PlaygroundHeight);
			//m_BackgroundBitmap = new Bitmap(m_BackgroundLayerBitmapData);	
			//addChild(m_BackgroundBitmap);
			
			m_AddRenderList = new Array();
			m_RemoveRenderList = new Array();
			
			m_PlaygroundLayerBitmapData = new BitmapData(DiggerSetting.m_ElementWidth * DiggerSetting.m_PlaygroundWidth, DiggerSetting.m_ElementHeight * DiggerSetting.m_PlaygroundHeight);
			m_PlaygroundBitmap = new Bitmap(m_PlaygroundLayerBitmapData);
			addChild(m_PlaygroundBitmap);
			
			m_Playground = new Array(DiggerSetting.m_PlaygroundHeight);
			for (var i:int = 0; i < DiggerSetting.m_PlaygroundWidth; ++i)
			{
				m_Playground[i] = new Array(DiggerSetting.m_PlaygroundWidth)
				for (var j:int = 0; j < DiggerSetting.m_PlaygroundHeight; ++j)
				{
					m_Playground[i][j] = new Element("element_ground");
					(m_Playground[i][j] as Element).m_Position = new Point(i * DiggerSetting.m_ElementWidth, j * DiggerSetting.m_ElementHeight);
					(m_Playground[i][j] as Element).Update();
				}
			}
			
			m_Player = new Player();
			addChild(m_Player.m_BitmapContainer);	
			addChild(new FPSCounter(new Point(600, 0)));
			
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
					if (Input.m_KeyboardCodes[37])
						m_Player.MoveRight();
					if (Input.m_KeyboardCodes[39])
						m_Player.MoveLeft();
					if (Input.m_KeyboardCodes[38])
						m_Player.MoveUp();
					if (Input.m_KeyboardCodes[40])
						m_Player.MoveDown();
				
					m_Player.Update();
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