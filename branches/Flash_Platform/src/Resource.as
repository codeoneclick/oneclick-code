package  
{
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Resource
	{
		public static var m_ContentLoader:ContentLoader;
		public static var m_ContainerPNG:Dictionary;
		
		public function Resource() 
		{
			m_ContainerPNG = new Dictionary();
			m_ContentLoader = new ContentLoader("content/");
		}	
	}

}