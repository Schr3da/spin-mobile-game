//
//  SubmenuViewController.h
//  spin
//
//  Created by schr3da on 10/07/15.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SubmenuView.h"

@interface SubmenuViewController : UIViewController{
    SubmenuView *submenuV;
}

@property (readwrite, nonatomic) BOOL isSubViewDisplayed;

@end