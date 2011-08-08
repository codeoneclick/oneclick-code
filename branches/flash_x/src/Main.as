package 
{
	import core.Global;
	import core.Input;
	import editor.EditorController;
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import core.Camera;
	import flash.utils.Dictionary;
	import game.SceneController;
	import ui.UIController;
	
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Main extends Sprite 
	{		
		private static const k_UI_LAYER:String = "UI_LAYER";
		private static const k_IN_GAME_LAYER:String = "IN_GAME_LAYER";
		private static const k_BACK_LAYER:String = "BACK_LAYER";
		private static const m_layerContainer:Dictionary = new Dictionary();
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			
			m_layerContainer[k_UI_LAYER] = new Sprite();
			m_layerContainer[k_IN_GAME_LAYER] = new Sprite();
			m_layerContainer[k_BACK_LAYER] = new Sprite();
			
			this.addChild(m_layerContainer[k_BACK_LAYER]);
			this.addChild(m_layerContainer[k_IN_GAME_LAYER]);
			this.addChild(m_layerContainer[k_UI_LAYER]);
			
			Global.stage = stage;
			Global.stage.scaleMode = StageScaleMode.NO_SCALE;
			Global.stage.frameRate = 60;
			Global.inGameContainer = m_layerContainer[k_IN_GAME_LAYER];
			Global.uiContainer = m_layerContainer[k_UI_LAYER];
			Global.backContainer = m_layerContainer[k_BACK_LAYER];
			Global.editorController = new EditorController();
			Global.sceneController = new SceneController();
			Global.sceneController.initDefault();
			Global.uiController = new UIController();
			Global.uiContainer.stage.align = StageAlign.TOP_LEFT;
			Global.input = new Input();
			Global.camera = new Camera();		
		}		
	}	
}