/*
 Copyright (c) 2011, OpenEmu Team
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

@import Cocoa;

#import "OEGridView.h"
#import "OEBlankSlateView.h"

#import "OELibrarySubviewController.h"
#import "OECollectionViewItemProtocol.h"

@class OETableView;
@class OELibraryController;
@class OEArrayController;

typedef NS_ENUM(NSInteger, OECollectionViewControllerViewTag) {
    OEBlankSlateTag = -1,
    OEGridViewTag   = 0,
    OEListViewTag   = 2
};

extern NSString  * _Nonnull  const OELastCollectionViewKey;

@interface OECollectionViewController : NSViewController <OEBlankSlateViewDelegate, NSTableViewDelegate, NSTableViewDataSource, OELibrarySubviewController, OEGridViewDelegate, OEGridViewMenuSource>

/// If YES, the collection view controller is selected and visible to the user. Must be overridden by subclasses.
@property (nonatomic, readonly) BOOL isSelected;

- (void)reloadData;
- (void)setNeedsReload;
- (void)setNeedsReloadVisible;
- (void)reloadDataIndexes:(NSIndexSet  * _Nullable )indexSet;
- (void)fetchItems;
- (NSArray * _Nonnull )defaultSortDescriptors;
- (void)setSortDescriptors:(NSArray* _Nullable )descriptors;

- (void)updateToolbar;
- (void)updateBlankSlate;
- (BOOL)shouldShowBlankSlate;

#pragma mark - State Management
- (void)storeStateWithKey:(NSString* _Nonnull)key;
- (void)restoreStateWithKey:(NSString* _Nonnull)key;
#pragma mark -
- (NSArray * _Nonnull )selectedGames;
@property (nonatomic) NSIndexSet * _Nonnull selectionIndexes;

#pragma mark - Toolbar
- (IBAction)switchToGridView:(id _Nullable)sender;
- (IBAction)switchToListView:(id _Nullable)sender;
- (IBAction)search:(id _Nullable)sender;
- (IBAction)changeGridSize:(id _Nullable)sender;

- (IBAction)deleteSelectedItems:(id _Nullable)sender;

#pragma mark - Context Menu
- (NSMenu* _Nullable)menuForItemsAtIndexes:(NSIndexSet* _Nullable)indexes;

#pragma mark -
- (id <OECollectionViewItemProtocol>  _Nullable)representedObject;

@property(nonatomic, readonly) OECollectionViewControllerViewTag selectedViewTag;
@property(nonatomic, weak) IBOutlet OELibraryController *libraryController;
@end

@interface OECollectionViewController ()
@property (assign) IBOutlet OETableView * _Nonnull listView;
@property (assign) IBOutlet OEGridView  * _Nonnull gridView;
@property (copy, nullable) NSString *currentSearchTerm;
- (void)OE_switchToView:(OECollectionViewControllerViewTag)tag;
- (void)OE_showView:(OECollectionViewControllerViewTag)tag;
- (void)OE_setupToolbarStatesForViewTag:(OECollectionViewControllerViewTag)tag;
- (void)OE_searchFor:( NSString *_Nullable)string;
@end
