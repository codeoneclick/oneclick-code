package game 
{
	import core.Global;
	import flash.display.Sprite;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class SceneController 
	{
		private static const k_TILE_WIDTH:int = 58;
		private static const k_TILE_HEIGHT:int = 16;
		
		private static const k_GAME_NODE_LAYER_01:String = "GAME_NODE_LAYER_01";
		private static const k_GAME_NODE_LAYER_02:String = "GAME_NODE_LAYER_02";
		
		private var m_gameNodeContainer:Vector.<GameNode> = new Vector.<GameNode>();
		private var m_characterNode:Character = null;
		
		private var m_visualLayers:Dictionary = new Dictionary();
		
		public function SceneController() 
		{
			m_visualLayers[k_GAME_NODE_LAYER_01] = new Sprite();
			Global.displayContainer.addChild(m_visualLayers[k_GAME_NODE_LAYER_01]);
			createMap( 12, 32 );
			
			m_visualLayers[k_GAME_NODE_LAYER_02] = new Sprite();
			Global.displayContainer.addChild(m_visualLayers[k_GAME_NODE_LAYER_02]);
			m_characterNode = new Character(m_visualLayers[k_GAME_NODE_LAYER_02]);
			m_characterNode.Load("character_01");
			m_visualLayers[k_GAME_NODE_LAYER_01].scaleX = 5;
		}
		
		public function createMap(_width:int, _height:int):void
		{
			for ( var j:int = 0; j < _height; j++ )
			{
				for ( var i:int = 0; i < _width; i++ )
				{	
					m_gameNodeContainer[i] = new GameNode(m_visualLayers[k_GAME_NODE_LAYER_01]);
					m_gameNodeContainer[i].Load("tile_01");
					if ( j % 2 > 0 )
					{
						m_gameNodeContainer[i].x = i * k_TILE_WIDTH;
						m_gameNodeContainer[i].y = j * k_TILE_HEIGHT;
					}
					else
					{
						m_gameNodeContainer[i].x = i * k_TILE_WIDTH + k_TILE_WIDTH / 2;
						m_gameNodeContainer[i].y = j * k_TILE_HEIGHT;
					}
				}
			}
		}
		
	}

}