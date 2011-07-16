package game 
{
	import core.Global;
	import fl.controls.Button;
	import flash.display.Sprite;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class SceneController 
	{
		private static const k_TILE_WIDTH:int = 90;
		private static const k_TILE_HEIGHT:int = 45;
		
		private var m_gameNodeContainer:Vector.<GameNode> = new Vector.<GameNode>();
		private var m_characterNode:Character = null;
		
		private var m_visualLayers:Dictionary = new Dictionary();	
		
		public function SceneController() 
		{
			createLayer( 12, 32, "layer_01" );
		}
		
		public function createLayer(_width:int, _height:int, _name:String):void
		{
			m_visualLayers[_name] = new LayerContainer(_name);
			Global.inGameContainer.addChild(m_visualLayers[_name]);
			createMap( _width, _height, (m_visualLayers[_name] as LayerContainer).getSubLayer(LayerContainer.k_TILE_LAYER) );
			createMap( _width, _height, (m_visualLayers[_name] as LayerContainer).getSubLayer(LayerContainer.k_OBJECT_LAYER) );
		}
		
		private function createMap(_width:int, _height:int, _container:Sprite):void
		{
			for ( var j:int = 0; j < _height; j++ )
			{
				for ( var i:int = 0; i < _width; i++ )
				{	
					m_gameNodeContainer[i] = new GameNode(_container);
					m_gameNodeContainer[i].Load("tile_00");
					if ( j % 2 > 0 )
					{
						m_gameNodeContainer[i].position.x = i * k_TILE_WIDTH;
						m_gameNodeContainer[i].position.y = j * k_TILE_HEIGHT / 2;
					}
					else
					{
						m_gameNodeContainer[i].position.x = i * k_TILE_WIDTH + k_TILE_WIDTH / 2;
						m_gameNodeContainer[i].position.y = j * k_TILE_HEIGHT / 2;
					}
				}
			}
		}
		
	}

}