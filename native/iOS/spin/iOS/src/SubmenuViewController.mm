//
//  SubmenuViewController.m
//  spin
//
//  Created by schr3da on 10/07/15.
//
//

#import "SubmenuViewController.h"
#import "Helper.h"

@implementation SubmenuViewController
@synthesize isSubViewDisplayed;

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initSubMenuV];
}

-(void)initSubMenuV{
    [Helper releaseViewObject:&submenuV];
    CGRect subframe = self.view.bounds;
    subframe.origin.y = [UIScreen mainScreen].bounds.size.height; //[Helper screenBorderOffset] + [Helper buttonSize].height;
    subframe.size.height = subframe.size.height;
    submenuV = [[SubmenuView alloc]initWithFrame:subframe];
    self.view = submenuV;
    self.isSubViewDisplayed = false;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

-(void)dealloc{
    
    [Helper removeSubviewsFromParent:&submenuV];
    [Helper releaseViewObject:&submenuV];
    [super dealloc];
}

@end
