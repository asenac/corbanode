{
  'targets': [
    {
      'target_name': 'corbanode',
      'cflags_cc!': [ '-fno-rtti'],
      'cflags_cc': [ '-fexceptions'],
      'include_dirs': [
        '/home/asenac/local/corbasim-trunk/include',
        '/home/asenac/local/ACE+TAO-5.7.9/include'
      ],
      'link_settings': {
          'ldflags': [
            '-L/home/asenac/local/corbasim-trunk/lib',
            '-L/home/asenac/local/ACE+TAO-5.7.9/lib',
          ],
          'libraries': [
            '-lACE',
            '-lTAO',
            '-lTAO_PortableServer',
            '-lTAO_AnyTypeCode',
            '-lTAO_CosNaming',
            '-lTAO_CosNaming_Skel',
            '-lTAO_ObjRefTemplate',
            '-lcorbasim',
          ]
      },
      'sources': [ 'addon.cc' ]
    }
  ]
}
