package 
{
	import Digger.DiggerGame;
	import Digger.Input;
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	/**
	 * ...
	 * @author OneClick
	 */
	public class Main extends Sprite 
	{
		
		private var m_GameCicleTimer:Timer;
		
		private var m_DiggerGame:DiggerGame;
		public  var m_CurrentGame:Object;
		private var m_Resource:Resource;
		private var m_Input:Input;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			m_Resource = new Resource();
			m_Input = new Input();
			m_GameCicleTimer = new Timer(1);
			m_GameCicleTimer.addEventListener(TimerEvent.TIMER, GameCicle);
			m_GameCicleTimer.start();
			m_DiggerGame = new DiggerGame();
			addChild(m_DiggerGame);
			m_CurrentGame = m_DiggerGame;	
			stage.frameRate = 60;
			stage.addEventListener(KeyboardEvent.KEY_DOWN, m_Input.OnKeyDown);
			stage.addEventListener(KeyboardEvent.KEY_UP, m_Input.OnKeyUp);
		}	
		
		private function GameCicle(event:TimerEvent):void
		{
			m_CurrentGame.Update();
			m_CurrentGame.Render();
		}
		
	}
	
}