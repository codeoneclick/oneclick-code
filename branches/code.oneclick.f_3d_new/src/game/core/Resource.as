package game.core 
{
	import common.loader.BitmapLoader;
	/**
	 * ...
	 * @author ...
	 */
	public class Resource 
	{
		public static const k_CONTENT_PATH:String = "Content/dev/";
		
		private static var m_bitmapLoader:BitmapLoader = null;
		
		public static function get bitmapLoader():BitmapLoader
		{
			if (m_bitmapLoader == null)
			{
				m_bitmapLoader = new BitmapLoader();
			}
			
			return m_bitmapLoader;
		}
		
	}

}