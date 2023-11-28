//
//  DocumentBrowserViewController.h
//  yale_ios
//
//  Created by Robert Baron on 9/29/19.
//  Copyright © 2019 Robert Baron. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DocumentBrowserViewController : UIDocumentBrowserViewController

- (void)presentDocumentAtURL:(NSURL *)documentURL;

@end
