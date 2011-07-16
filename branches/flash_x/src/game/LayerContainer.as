package game 
{
	import adobe.utils.CustomActions;
	import flash.display.Sprite;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class LayerContainer extends Sprite
	{
		public static const k_TILE_LAYER:String = "TILE_LAYER";
		public static const k_OBJECT_LAYER:String = "OBJECT_LAYER";
		
		private var m_subLayers:Dictionary = new Dictionary();;
		
		private var m_name:String = "";
		
		public function LayerContainer(_name:String) 
		{
			m_name = _name;
			init();
		}
		
		private function init():void
		{
			m_subLayers[k_TILE_LAYER] = new Sprite();
			this.addChild(m_subLayers[k_TILE_LAYER]);
			
			m_subLayers[k_OBJECT_LAYER] = new Sprite();
			this.addChild(m_subLayers[k_OBJECT_LAYER]);
		}
		
		public function getSubLayer(_value:String):Sprite
		{
			return m_subLayers[k_OBJECT_LAYER];
		}
		
	}

}